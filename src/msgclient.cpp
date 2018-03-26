#include "msgclient.h"

MsgClient::MsgClient(string receiver, string msg)
{
    this->receiver = receiver;
    this->msg = msg;
    this->send_sock = new TCPSocket();
}

void MsgClient::Start()
{
    if (CheckReceiver())
    {
#ifdef MSGCLIENT_LOG
        cout << "Find a client" << endl;
#endif
        if(SetRoute())
        {
            SendMsg();
        }
        else
        {
            cout << "Fail to set route" << endl;
        }
    }
    else
    {
//#ifdef MSGCLIENT_LOG
        cout << "No such a client" << endl;
//#endif
    }
}

bool MsgClient::CheckReceiver()
{
    if(UserInfoMap.find(this->receiver) == UserInfoMap.end())
        return false;
    return true;
}
bool MsgClient::SetRoute()
{
    int i, j= 0;
    int maxsize = UserInfoMap.size();
    if(maxsize > 2 && maxsize < 100)
    {
        for(i = 0; i < maxsize; i++)
            node_list[i]="";

        i = 0;
        for(std::pair<std::string, UserInfo*> element : UserInfoMap)
        {
            node_list[i]=element.first;
            i++;
        }
        j = 0;
        srand(time(NULL));
        for(i = maxsize-1 ; i > 0; i--)
        {
            j = rand() % i;
            std::swap(node_list[i], node_list[j]);
        }
#ifdef MSGCLIENT_LOG
        for(i = 0; i < maxsize; i++)
            cout << "[D]"<<node_list[i] <<endl;
#endif
    }
    else
    {
        cout << "NODE ARE NOT EHOUGH" << endl;
        return false;
    }
    return true;
}

int MsgClient::SendMsg()
{
    int rv = 0;
    string recv_ip = ((UserInfo*)(UserInfoMap[this->node_list[0]]))->GetIpAddr();
    this->send_sock->Connect(recv_ip);
#ifdef MSGCLIENT_LOG
    cout << recv_ip << endl;
#endif
    rv += SendLength();
    rv += SendData();
    return rv;
}

int MsgClient::SendLength()
{
    int rv = 0;
    Json::Value root;
    root["sender"] = myInfo->GetGithubId();
    root["receiver"] = this->receiver;
    root["length"] = this->msg.length();
    rv = this->send_sock->Send(root.toStyledString());
    return rv;
}

int MsgClient::SendData()
{
    int rv = 0;
    Json::Value root;
    root["sender"] = myInfo->GetGithubId();
    root["receiver"] = this->receiver;
    root["data"] = this->msg;
    rv = this->send_sock->Send(root.toStyledString());
    return rv;
}

int MsgClient::EncryptMsg(string data)
{
	return 0;
}

MsgClient::~MsgClient()
{

}
