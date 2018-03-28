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
    int i=0, j= 0;
    int node_list_size  = 0;
    int rnd             = 0;
    int maxsize         = UserInfoMap.size();
    string my_github_id = myInfo->GetGithubId();

    srand(time(NULL));
    if(maxsize > 2 && maxsize < 100)
    {
        // initialize
        for(i = 0; i < maxsize; i++) node_list[i]="";
        for(std::pair<std::string, UserInfo*> element : UserInfoMap)
         {
            if(element.first != this->receiver && element.first != my_github_id)
            {
                node_list[node_list_size]=element.first;
                node_list_size++;
            }
        }
    cout << "[D]3" << endl;
        // randomize node list except src and dest.
        for(i = node_list_size-1; i >=0; i--)
        {
            if(i==0)break;
            else
            {
                j = rand() % i;
                std::swap(node_list[i], node_list[j]);
            }
        }
        rnd = rand() % (maxsize-2);
        this->route_length =rnd+2;
        node_list[rnd+1] = this->receiver;

//#ifdef MSGCLIENT_LOG
        for(i = 0; i < this->route_length; i++)
            cout << "[D2]msgClient : node list " << node_list[i] << endl;
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
    for(int i = this->route_length; i>1 ; i--)
    {
        string receiver = this->node_list[i-1];
        string sender = this->node_list[i-2];
        //data = PGP->Encrypt(GetPGPKeyId(receiver), data);

        Json::Value root;
        root["sender"] = sender;
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
