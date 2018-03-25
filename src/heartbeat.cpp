#include "heartbeat.h"

Heartbeat::Heartbeat(map<string, UserInfo>* UserInfoMap)
{
    Initialize();
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
    this->send_sock->SetSockOpt(SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof broadcast);
    this->recv_sock->SetSockOpt(SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof broadcast);

    this->send_sock->Bind(HEARTBEAT_SEND_PORT);
    this->recv_sock->Bind(HEARTBEAT_RECV_PORT);

    this->send_sock->SetDestAddr(BROADCAST_ADDR, HEARTBEAT_SEND_PORT);
    return 0;
}

void Heartbeat::Start()
{
	std::thread send_broadcast_thread([this] { SendBroadcast();} );
    std::thread recv_broadcast_thread([this] { RecvBroadcast();} );
    send_broadcast_thread.join();
    recv_broadcast_thread.join();
}

void Heartbeat::SendBroadcast()
{
    int rv;
    std::chrono::seconds period(BROADCAST_PERIOD);

    while(1)
    {
        Json::Value root;
        root["github_id"] = myInfo->GetGithubId();
        root["pgp_key_id"] = myInfo->GetPGPKeyId();

        Json::StyledWriter writer;
        std::string information = writer.write( root );
        rv = this->send_sock->Send(information);
        cout << "Send Broadcast" << endl;
        std::this_thread::sleep_for(period);
    }
}

void Heartbeat::RecvBroadcast()
{
    // Thread
    // if new user info
    // userinfo.getmail
    // pgp.searchkeys
    // updateUserinfo
}

