#include "heartbeat.h"

Heartbeat::Heartbeat(){}
Heartbeat::~Heartbeat(){}

void Heartbeat::Start()
{
    // start threads sending and recving BC msg
	std::thread send_broadcast_thread([this] { SendBroadcast();} );
    std::thread recv_broadcast_thread([this] { RecvBroadcast();} );
    send_broadcast_thread.detach();
    recv_broadcast_thread.detach();
}

void Heartbeat::SendBroadcast()
{
    int rv = 0;
    int broadcast = 1;
    const char *broadcast_addr = "255.255.255.255";

    // Create socket and set up for broadcasting
    UDPSocket* send_sock;
    send_sock = new UDPSocket();
    if (!send_sock->Valid()) exit(-1);
    rv = send_sock->SetSockOpt(SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof broadcast);
    if (rv == -1) exit(-1);
    rv = send_sock->Bind(HEARTBEAT_SEND_PORT);
    if (rv < 0) exit(-1);
    send_sock->SetDestAddr(broadcast_addr, HEARTBEAT_RECV_PORT);

    std::chrono::seconds period(BROADCAST_PERIOD);

    while(1)
    {
        // make data to json format
        Json::Value root;
        root["flag"] = 1;
        root["github_id"] = myInfo->GetGithubId();
        root["pgp_key_id"] = myInfo->GetPGPKeyId();

        rv = send_sock->Send(root.toStyledString());
#ifdef HEARTBEAT_LOG
        if (rv > 0)
          cout << "Send Broadcast" << endl;
#endif
        // delay 1s
        std::this_thread::sleep_for(period);
    }
}

void Heartbeat::RecvBroadcast()
{
    int rv;
    int broadcast = 1;
    // Create socket for receiving broadcast message
    UDPSocket *recv_sock = new UDPSocket();
    if (!recv_sock->Valid()) exit(-1);
    recv_sock = new UDPSocket();
    recv_sock->SetSockOpt(SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof broadcast);
    if (rv == -1) exit(-1);
    recv_sock->Bind(HEARTBEAT_RECV_PORT);
    if (rv < 0) exit(-1);

    string *data;

    while(1)
    {
        // recv data
        data = recv_sock->Recv();
#ifdef HEARTBEAT_LOG
        cout << "Recv Broadcast" << endl;
#endif
        // parse data to json format
        JSONCPP_STRING errs;
        Json::Value root;
        Json::CharReaderBuilder builder;
        Json::CharReader * reader = builder.newCharReader();
        reader->parse(data[0].c_str(), data[0].c_str()+data[0].length(), &root, &errs);

        // parsing error handling
        if(errs.find("error") !=string::npos)
        {
            cout << "[Error!] Not Json Format" << endl;
            continue;
        }

        // get json data
        Json::Value j_flag = root["flag"];
        Json::Value j_github_id = root["github_id"];
        Json::Value j_pgp_key_id = root["pgp_key_id"];

        if(j_flag.isNull() || j_github_id.isNull() || j_pgp_key_id.isNull())
        {
            cout << "[Error!] Invalid Json Format" << endl;
            continue;
        }

        // cast json data
        int flag = j_flag.asInt();
        string github_id = j_github_id.asCString();
        string pgp_key_id = j_pgp_key_id.asCString();

        // check if pgp key id is valid
        if(HackDetector(pgp_key_id))
            continue;

        // process data
        if(flag) // live Client
        {
            if(UserInfoMap.find(github_id) == UserInfoMap.end()) // new Client
            {
                // Add new Client
                UserInfo* newUser = new UserInfo();
                newUser->SetGithubId(github_id);
                newUser->SetIpAddr(data[1]);
                newUser->SetPGPKeyId(pgp_key_id);
#ifdef HEARTBEAT_LOG
                cout << UserInfoMap.size() << endl;
#endif
                UserInfoMap.insert(std::pair<string, UserInfo*>(github_id, newUser));

                // update my data
                if(!myInfo->GetGithubId().compare(github_id))
                    myInfo->SetIpAddr(data[1]);

#ifdef HEARTBEAT_LOG
                cout << UserInfoMap.size() << endl;
                cout << UserInfoMap[github_id]->GetGithubId() << endl;
                cout << UserInfoMap[github_id]->GetIpAddr() << endl;
                cout << UserInfoMap[github_id]->GetPGPKeyId() << endl;
#endif
            }
            else // update data
            {
                UserInfoMap[github_id]->SetIpAddr(data[1]);
                UserInfoMap[github_id]->SetPGPKeyId(pgp_key_id);
#ifdef HEARTBEAT_LOG
                cout << UserInfoMap[github_id]->GetGithubId() << endl;
                cout << UserInfoMap[github_id]->GetIpAddr() << endl;
                cout << UserInfoMap[github_id]->GetPGPKeyId() << endl;
#endif
            }
        }
        else    // dead Client
        {
#ifdef HEARTBEAT_LOG
                cout << UserInfoMap.size() << endl;
#endif
            if(UserInfoMap.find(github_id) != UserInfoMap.end()) // to delete
            {
                delete UserInfoMap[github_id];
                UserInfoMap.erase(github_id);
            }
#ifdef HEARTBEAT_LOG
                cout << UserInfoMap.size() << endl;
#endif
        }
    }
}

void Heartbeat::SendKill()
{
    // When messenger die, Send kill message for updating peer list
    int rv;
    int broadcast = 1;
    const char *broadcast_addr = "255.255.255.255";

    // Create socket and setting for broadcasting
    UDPSocket* send_sock = new UDPSocket();
    if (!send_sock->Valid()) exit(-1);
    rv = send_sock->SetSockOpt(SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof broadcast);
    if (rv == -1) exit(-1);
    rv = send_sock->Bind(HEARTBEAT_KILL_PORT);
    if (rv < 0) exit(-1);
    send_sock->SetDestAddr(broadcast_addr, HEARTBEAT_RECV_PORT);

    // make data to json format
    Json::Value root;
    root["flag"] = 0;
    root["github_id"] = myInfo->GetGithubId();
    root["pgp_key_id"] = myInfo->GetPGPKeyId();

    // Send json data
    send_sock->Send(root.toStyledString());
    delete send_sock;
}

int Heartbeat::HackDetector(string str)
{
    // Check Valid PGP KEY ID
    std::regex reg("[^a-zA-Z0-9]*");
    smatch match;
    if(regex_match(str, match, reg))
    {
        cout << "[Error!] Hack detection" << endl;
        return 1;
    }
    else
        return 0;
}

