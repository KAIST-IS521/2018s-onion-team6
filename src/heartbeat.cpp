#include "heartbeat.h"

Heartbeat::Heartbeat()
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
	this->_send_sock = new UDPSocket();
    this->_recv_sock = new UDPSocket();
    return 0;
}

int Heartbeat::SetSocket()
{
	int broadcast = 1;
    this->_send_sock->SetSockOpt(SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof broadcast);
    this->_recv_sock->SetSockOpt(SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof broadcast);

    this->_send_sock->Bind(HEARTBEAT_SEND_PORT);
    this->_recv_sock->Bind(HEARTBEAT_RECV_PORT);

    this->_send_sock->SetDestAddr(BROADCAST_ADDR, HEARTBEAT_SEND_PORT);
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
	int rv = 0;
    int len = 0;
    char data[MAX_BUF_LEN];
    std::chrono::seconds period(BROADCAST_PERIOD);

    while(1)
    {
        memcpy(data, "Github Id", strlen("Github Id"));
        len = strlen(data);
        rv = this->_send_sock->Send(data, len);
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

