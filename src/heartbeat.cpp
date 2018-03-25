#include "heartbeat.h"

Heartbeat::Heartbeat()
{
    //Initialize();
}

int Heartbeat::Initialize()
{
    CreateSocket();
    SetSocket();
    return 0;
}

int Heartbeat::CreateSocket()
{
    this->send_sock = new UDPSocket();
    this->recv_sock = new UDPSocket();
    return 0;
}

int Heartbeat::SetSocket()
{
	int broadcast = 1;
    const char *broadcast_addr = "255.255.255.255";

    // set socket option
    this->send_sock->SetSockOpt(SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof broadcast);
    this->recv_sock->SetSockOpt(SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof broadcast);

    // bind socket addr
    this->send_sock->Bind(HEARTBEAT_SEND_PORT);
    this->recv_sock->Bind(HEARTBEAT_RECV_PORT);

    // set send socket's dest addr
    this->send_sock->SetDestAddr(broadcast_addr, HEARTBEAT_RECV_PORT);
    return 0;
}

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

    this->send_sock = new UDPSocket();
    this->send_sock->SetSockOpt(SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof broadcast);
    this->send_sock->Bind(HEARTBEAT_SEND_PORT);
    this->send_sock->SetDestAddr(broadcast_addr, HEARTBEAT_RECV_PORT);


    int rv = 0;
    std::chrono::seconds period(BROADCAST_PERIOD);

    while(1)
    {
        // make data to json format
        Json::Value root;
        root["flag"] = 1;
        root["github_id"] = myInfo->GetGithubId();
        root["pgp_key_id"] = myInfo->GetPGPKeyId();

        // json data to string
        Json::StyledWriter writer;
        std::string information = writer.write( root );

        // send data
        rv = this->send_sock->Send(information);
        if (rv > 0)
#ifdef DEBUG
          cout << "Send Broadcast" << endl;
#endif
        // delay 1s
        std::this_thread::sleep_for(period);
    }
}

void Heartbeat::RecvBroadcast()
{

    int broadcast = 1;
    this->recv_sock = new UDPSocket();
    this->recv_sock->SetSockOpt(SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof broadcast);
    this->recv_sock->Bind(HEARTBEAT_RECV_PORT);


    string *data;

    while(1)
    {
        // recv data
        data = this->recv_sock->Recv();
#ifdef DEBUG
        cout << "Recv Broadcast" << endl;
#endif
        // parse data to json format
        Json::Value root;
        Json::Reader reader;
        if(!reader.parse(data[0], root))
            cout << "Parse error" << endl;

        // get json data
        Json::Value j_flag = root["flag"];
        Json::Value j_github_id = root["github_id"];
        Json::Value j_pgp_key_id = root["pgp_key_id"];

        // cast json data
        int flag = j_flag.asInt();
        string github_id = j_github_id.asCString();
        string pgp_key_id = j_pgp_key_id.asCString();

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
#ifdef DEBUG
                cout << UserInfoMap.size() << endl;
#endif
                UserInfoMap.insert(std::pair<string, UserInfo*>(github_id, newUser));
#ifdef DEBUG
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
#ifdef DEBUG
                cout << UserInfoMap[github_id]->GetGithubId() << endl;
                cout << UserInfoMap[github_id]->GetIpAddr() << endl;
                cout << UserInfoMap[github_id]->GetPGPKeyId() << endl;
#endif
            }
        }
        else    // dead Client
        {
#ifdef DEBUG
                cout << UserInfoMap.size() << endl;
#endif
            if(UserInfoMap.find(github_id) != UserInfoMap.end()) // to delete
                UserInfoMap.erase(github_id);
#ifdef DEBUG
                cout << UserInfoMap.size() << endl;
#endif
        }
    }
}

