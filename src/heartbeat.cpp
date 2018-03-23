nclude "heartbeat.h"

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
}

void Heartbeat::SendBroadcast()
{
}

void Heartbeat::RecvBroadcast()
{
    // Thread
    // if new user info
    // userinfo.getmail
    // pgp.searchkeys
    // updateUserinfo
}

