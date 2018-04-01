#include "msgclient.h"

MsgClient::MsgClient(string receiver, string msg)
{
    this->receiver = receiver;
    this->msg = msg;
    this->send_sock = new TCPSocket();
}

void MsgClient::Start()
{
    // Check if receiver exists
    if (CheckReceiver())
    {
        // Set route and send msg
        if(SetRoute())
        {
            if(SendMsg() < 0)
            {
                cout << "[Error!] Fail to send message" << endl;
            }
        }
        else
        {
            cout << "[Error!] Fail to set route" << endl;
        }
    }
    else
        cout << "[Error!] No such a client" << endl;
}

bool MsgClient::CheckReceiver()
{
    // Find receiver in peer list
    if(UserInfoMap.find(this->receiver) == UserInfoMap.end())
        return false;
    return true;
}

bool MsgClient::SetRoute()
{
    int i = 0, j = 0;
    int node_list_size = 0; // node list index
    int rnd = 0; // # of routes
    int maxsize = UserInfoMap.size(); // # of clients

    string my_github_id = myInfo->GetGithubId();

    srand(time(NULL));
    if(maxsize > 2 && maxsize < 100)
    {
        // initialize
        for(i = 0; i <= maxsize; i++) node_list[i]="";
        for(std::pair<std::string, UserInfo*> element : UserInfoMap)
         {
            // set node list except src and dst
            if(element.first != this->receiver && element.first != my_github_id)
            {
                node_list_size++;
                node_list[node_list_size]=element.first;
            }
        }
        // randomize node list except src and dst
        for(i = node_list_size; i >0; i--)
        {
            if(i==0) break;
            else
            {
                j = rand() % i;
                if( j == 0 )
                {
                    continue;
                }
                else
                {
                    std::swap(node_list[i], node_list[j]);
                }

            }
        }
        // Set # of routes randomly
        rnd = rand() % maxsize;
        if(rnd < 2) rnd = maxsize-1;

        this->route_length = rnd + 1; // route length

        node_list[rnd] = this->receiver; // set receiver
        node_list[0] = my_github_id; // set sender

#ifdef MSGCLIENT_LOG
        for(i = 0; i < this->route_length; i++)
            cout << "[D2]msgClient : node list " << node_list[i] << endl;
#endif
    }
    else
    {
        cout << "[Error!] Node are not enough" << endl;
        return false;
    }
    return true;
}

int MsgClient::SendMsg()
{
    int rv;
    // Set receiver
    string recv_ip = GetIpAddress(this->node_list[1]);
    rv = this->send_sock->Connect(recv_ip, MSG_SERVER_PORT);
    if (rv < 0)
        return rv;

    // Send msg
    return SendData();
}

int MsgClient::SendData()
{
    int rv = 0;
    string data = "";

    // Make data to json format
    Json::Value root;
    root["sender"] = myInfo->GetGithubId();
    root["receiver"] = this->receiver;
    root["data"] = this->msg;
    data = root.toStyledString();

    // Encrypt data and send it
    data = EncryptMsg(data);
    if(!data.compare(""))
    {
        cout << "[Error!] Encrypt data" << endl;
        return -1;
    }
    else
        rv = this->send_sock->Send(data);

    return rv;
}

string MsgClient::EncryptMsg(string data)
{
    for(int i = this->route_length; i>1 ; i--)
    {
        // Set receiver, sender, pgp key id
        string receiver = this->node_list[i-1];
        string sender = this->node_list[i-2];
        string pub_key_id = ((UserInfo*)UserInfoMap[receiver])->GetPGPKeyId();

        // encrypt data using receiver's pgp key
        data = pgpmanager->EncryptData(pub_key_id, data);
        if (!data.compare(""))
            return data;
        if (i==2)
            break;
        Json::Value root;
        root["sender"] = sender;
        root["receiver"] = receiver;
        root["data"] = data;
        data = root.toStyledString();
    }
#ifdef MSGCLIENT_LOG
    cout << data << endl;
#endif
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
