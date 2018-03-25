#include "msgclient.h"

MsgClient::MsgClient(string receiver, string msg)
{
    this->receiver = receiver;
    this->msg = msg;
}

void MsgClient::Start()
{
    if (CheckReceiver())
    {
        SetRoute();
        SendMessage();
    }
}

bool MsgClient::CheckReceiver()
{
    if(UserInfoMap.find(this->receiver) == UserInfoMap.end())
        return false;
    return true;
}

void MsgClient::SetRoute()
{

}

int MsgClient::SendMessage()
{

}
