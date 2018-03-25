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
        SetRoute();
        SendMsg();
    }
    else
    {
#ifdef MSGCLIENT_LOG
        cout << "No such a client" << endl;
#endif
    }
}

bool MsgClient::CheckReceiver()
{
    if(UserInfoMap.find(this->receiver) == UserInfoMap.end())
        return false;
    return true;
}
int MsgClient::SetRoute()
{
	int i = 0;
    int maxsize = UserInfoMap.size();
    if(maxsize > 2 && maxsize < 100 )
    {
        for(i = 0; i < maxsize; i++)
        {
            node_list[i]="";
        }
        i=0;

        for (std::pair<std::string, UserInfo * > element : UserInfoMap )
        {
            node_list[i]=element.first;
            i++;
        }
        int j = 0;
        string tmp;
        srand(time(NULL));
        for(i = maxsize-1 ; i > 0; i--)
        {
            j = rand() % i;
            std::swap(node_list[i],node_list[j]);
        }

        //for(i = 0; i < maxsize; i++)
        //    cout << "[D]"<<node_list[i] <<endl;
    }
    else
    {
        cout << "NODE ARE NOT EHOUGH" <<endl;
        exit(0);
    }
    return 0;
}

int MsgClient::SendMsg()
{
    string recv_ip = ((UserInfo*)(UserInfoMap[this->node_list[0]]))->GetIpAddr();
    this->send_sock->Connect(recv_ip);
#ifdef MSGCLIENT_H
    cout << recv_ip << endl;
#endif
    //this->send_sock->Connect("127.0.0.1");
    SendLength();
    SendData();
}

int MsgClient::SendLength()
{
    Json::Value root;
    root["sender"] = myInfo->GetGithubId();
    root["receiver"] = this->receiver;
    root["length"] = this->msg.length();

    Json::StyledWriter writer;
    std::string data = writer.write( root );

    EncryptMsg(data);
    this->send_sock->Send(data);

}

int MsgClient::SendData()
{
    Json::Value root;
    root["sender"] = myInfo->GetGithubId();
    root["receiver"] = this->receiver;
    root["data"] = this->msg;

    Json::StyledWriter writer;
    std::string data = writer.write( root );

    EncryptMsg(data);
    this->send_sock->Send(data);
}

int MsgClient::EncryptMsg(string data)
{
	return 0;
}
