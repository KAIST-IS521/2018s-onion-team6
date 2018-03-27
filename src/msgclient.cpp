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
    string my_github_id = myInfo->GetGithubId();

    if(maxsize > 2 && maxsize < 100)
    {
        // initialize
        for(i = 0; i < maxsize; i++)
            node_list[i]="";

        i = 0;
        for(std::pair<std::string, UserInfo*> element : UserInfoMap)
        {
            // except for sender, receiver
            if(element.first != this->receiver && element.first != my_github_id)
            {
                node_list[i]=element.first;
                i++;
            }
        }

        srand(time(NULL));

//#ifdef MSGCLIENT_LOG
        for(i = 0; i < maxsize-2; i++)
            cout << "[D1]_node list "<<node_list[i] << endl;
//#endif

        // randomize
        for(i = maxsize-3; i > 0; i--)
        {
            j = rand() % i;
            std::swap(node_list[i], node_list[j]);
        }

        // need to fix
        this->route_length = maxsize-1;

        node_list[route_length-1] = this->receiver;
//#ifdef MSGCLIENT_LOG
        for(i = 0; i < maxsize-1; i++)
            cout << "[D2]_node list " << node_list[i] << endl;
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
    string recv_ip = GetIpAddress(this->node_list[0]);
    this->send_sock->Connect(recv_ip);

#ifdef MSGCLIENT_LOG
    cout << recv_ip << endl;
#endif
    rv += SendData();
    return rv;
}

    return SendData();
}

int MsgClient::SendData()
{
    int rv = 0;
    string data = "";

    Json::Value root;
    root["sender"] = myInfo->GetGithubId();
    root["receiver"] = this->receiver;
    root["data"] = this->msg;
    data = root.toStyledString();

    data = EncryptMsg(data);
    rv = this->send_sock->Send(data);

    return rv;
}

string MsgClient::EncryptMsg(string data)
{
    for(int i = this->route_length; i>0 ; i--)
    {
        string receiver = this->node_list[i-1];
        //data = PGP->Encrypt(GetPGPKeyId(receiver), data);

        Json::Value root;
        root["receiver"] = receiver;
        root["data"] = data;
        data = root.toStyledString();
    }
//#ifdef MSGCLIENT_LOG
    cout << data << endl;
//#endif
    return data;
}

MsgClient::~MsgClient()
{

}

string MsgClient::GetIpAddress(string github_id)
{
    return ((UserInfo*)(UserInfoMap[github_id]))->GetIpAddr();
}

string MsgClient::GetPGPKeyId(string github_id)
{
    return ((UserInfo*)(UserInfoMap[github_id]))->GetPGPKeyId();
}
