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
    string myGitId = myInfo->GetGithubId();

    if(maxsize > 1 && maxsize < 100)
    {
        for(i = 0; i < maxsize; i++)
        {
            node_list[i]="";
        }

        i = 0;
        for(std::pair<std::string, UserInfo*> element : UserInfoMap)
        {
            if(element.first != this->receiver && element.first != myGitId)
            {
                node_list[i]=element.first;
                i++;
            }
        }

        j = 0;
        srand(time(NULL));

        for(i = 0; i < maxsize-2; i++)
        {
            cout << "[D1]_node list "<<node_list[i] << endl;
        }

        // list -=  myid -= receive id;
        if(maxsize > 2)
        {
            for(i = maxsize-3; i > 0; i--)
            {
                j = rand() % i;
                std::swap(node_list[i], node_list[j]);
            }
        }

        node_list[maxsize-2] = this->receiver;
//#ifdef MSGCLIENT_LOG
        for(i = 0; i < maxsize-1; i++)
        {
            cout << "[D2]_node list "<<node_list[i] << endl;
        }
//#endif
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
    string recv_ip = ((UserInfo*)(UserInfoMap[this->node_list[0]]))->GetIpAddr();
    this->send_sock->Connect(recv_ip);

#ifdef MSGCLIENT_LOG
    cout << recv_ip << endl;
#endif

    return SendData();
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
