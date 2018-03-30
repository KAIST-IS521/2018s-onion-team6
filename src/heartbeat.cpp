#include "heartbeat.h"

Heartbeat::Heartbeat()
{
    //Initialize();
}
/*
int Heartbeat::Initialize()
{
    CreateSocket();
    SetSocket();
    return 0;
}

int Heartbeat::CreateSocket()
{
    this->send_sock = new UDPSocket();
    //this->recv_sock = new UDPSocket();
    cout << this->send_sock << endl;
    return 0;
}

int Heartbeat::SetSocket()
{
	int broadcast = 1;
    const char *broadcast_addr = "255.255.255.255";

    // set socket option
    this->send_sock->SetSockOpt(SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof broadcast);
    //this->recv_sock->SetSockOpt(SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof broadcast);

    // bind socket addr
    this->send_sock->Bind(9999);
    //this->send_sock->Bind(HEARTBEAT_SEND_PORT);
    //this->recv_sock->Bind(HEARTBEAT_RECV_PORT);

    // set send socket's dest addr
    this->send_sock->SetDestAddr(broadcast_addr, HEARTBEAT_RECV_PORT);
    return 0;
}
*/
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
    int broadcast = 1;
    const char *broadcast_addr = "255.255.255.255";

    UDPSocket* send_sock;
    send_sock = new UDPSocket();
    send_sock->SetSockOpt(SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof broadcast);
    send_sock->Bind(HEARTBEAT_SEND_PORT);
    send_sock->SetDestAddr(broadcast_addr, HEARTBEAT_RECV_PORT);
//    this->send_sock = new UDPSocket();
//    this->send_sock->SetSockOpt(SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof broadcast);
//    this->send_sock->Bind(HEARTBEAT_SEND_PORT);
//    this->send_sock->SetDestAddr(broadcast_addr, HEARTBEAT_RECV_PORT);

    int rv = 0;
    std::chrono::seconds period(BROADCAST_PERIOD);

    while(1)
    {
        // make data to json format
        Json::Value root;
        root["flag"] = 1;
        root["github_id"] = myInfo->GetGithubId();
        root["pgp_key_id"] = myInfo->GetPGPKeyId();

        //rv = this->send_sock->Send(root.toStyledString());
        rv = send_sock->Send(root.toStyledString());
        if (rv > 0)
#ifdef HEARTBEAT_LOG
          cout << "Send Broadcast" << endl;
#endif
        // delay 1s
        std::this_thread::sleep_for(period);
    }
}

void Heartbeat::RecvBroadcast()
{
    int broadcast = 1;
    UDPSocket *recv_sock = new UDPSocket();
    recv_sock = new UDPSocket();
    recv_sock->SetSockOpt(SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof broadcast);
    recv_sock->Bind(HEARTBEAT_RECV_PORT);

//    this->recv_sock = new UDPSocket();
//    this->recv_sock->SetSockOpt(SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof broadcast);
//    this->recv_sock->Bind(HEARTBEAT_RECV_PORT);

    string *data;

    while(1)
    {
        // recv data
        //data = this->recv_sock->Recv();
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

        // get json data
        Json::Value j_flag = root["flag"];
        Json::Value j_github_id = root["github_id"];
        Json::Value j_pgp_key_id = root["pgp_key_id"];

        // cast json data
        int flag = j_flag.asInt();
        string github_id = j_github_id.asCString();
        string pgp_key_id = j_pgp_key_id.asCString();

        if(hackDetector(pgp_key_id))
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
                UserInfoMap.erase(github_id);
#ifdef HEARTBEAT_LOG
                cout << UserInfoMap.size() << endl;
#endif
        }
    }
}

void Heartbeat::SendKill()
{
    int broadcast = 1;
    const char *broadcast_addr = "255.255.255.255";

    UDPSocket* send_sock = new UDPSocket();
    send_sock->SetSockOpt(SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof broadcast);
    send_sock->Bind(HEARTBEAT_KILL_PORT);
    send_sock->SetDestAddr(broadcast_addr, HEARTBEAT_RECV_PORT);

    // make data to json format
    Json::Value root;
    root["flag"] = 0;
    root["github_id"] = myInfo->GetGithubId();
    root["pgp_key_id"] = myInfo->GetPGPKeyId();
    send_sock->Send(root.toStyledString());
}



int Heartbeat::hackDetector(string v1)
{
    std::regex reg("[^a-zA-Z0-9]*");
    smatch match;
    if(regex_match(v1, match, reg))
    {
        cout << "HACK DETECTION" << endl;
        return 1;
    }
    else
    {
        return 0;
    }
}

