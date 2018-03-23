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
}

int Heartbeat::SetSocket()
{
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

