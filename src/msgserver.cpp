#include "msgserver.h"

MsgServer::MsgServer(){}

void MsgServer::Start()
{
    // start threads recving msg
    std::thread serverRun([this] { RecvServer();});
    serverRun.detach();
}

void MsgServer::RecvServer()
{
    // Create Server socket and listen
    int rv;
    int yes = 1;
    this->server_sock = new TCPSocket();
    if(!this->server_sock->Valid()) exit(-1);
    rv = this->server_sock->SetSockOpt(SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
    if (rv == -1) exit(-1);
    rv = this->server_sock->Bind(SERVER_SOCK);
    if (rv < 0) exit(-1);
    rv = this->server_sock->Listen(10);
    if (rv < 0) exit(-1);

    while (true)
    {
        // when get msg, create thread for receiving and forwarding msg
        this->client_sock = this->server_sock->Accept();
        if(!this->client_sock->Valid())
        {
            delete this->client_sock;
            continue;
        }
        std::thread acceptRun([this] { Worker(this->client_sock); });
        acceptRun.detach();
    }
    delete this->client_sock;
}

void MsgServer::Worker(TCPSocket* client_sock)
{
    while (true)
    {
        // recv msg
        std::string msg;
        if (client_sock->Recv(msg) <= 0)
            break;

        // decrypt and parse msg
        string decrypted_msg = pgpmanager->DecryptData(msg);
        if(decrypted_msg != "")
            this->JsonParsor(decrypted_msg);
    }
    delete client_sock;
}

string MsgServer::SaveFile(string file_name, string data)
{
    size_t tokenlen=0;

    // directory traversal mitigation
    while( file_name.find("/") != string::npos )
    {
         tokenlen = file_name.find("/");
         file_name = file_name.substr(tokenlen+1);
    }
    string file_path = "./MSG/" + file_name;

    // save msg
    ofstream write_file(file_path.data(), ios::app);
    if(write_file.is_open())
    {
        write_file << data << endl;
        write_file.close();
    }
    else
    {
        cout << "[Error!] File open error " << file_path << endl;
        exit(0);
    }
    return file_path;
}

int MsgServer::JsonParsor(string msg)
{
    JSONCPP_STRING errs;
    Json::Value root;
    Json::CharReaderBuilder builder;
    Json::CharReader * reader = builder.newCharReader();

    string github_id;
    string receiver_id;
    string data;

    // parse decrypted msg
    reader->parse(msg.c_str(), msg.c_str()+msg.length(), &root, &errs);
    if(errs.find("error") != string::npos)
    {
        cout << "[Error!] Not JSON Format" << endl;
        return 0;
    }

    // get data from parsed msg
    Json::Value j_sender    = root["sender"];
    Json::Value j_receiver  = root["receiver"];
    Json::Value j_data      = root["data"];
    if(j_sender.isNull() || j_receiver.isNull() || j_data.isNull())
    {
        cout << "[Error!] Invalid Json Fromat" << endl;
        return 0;
    }
    github_id = j_sender.asCString();
    receiver_id = j_receiver.asCString();
    data = j_data.asCString();

    // my msg, receive it
    if(receiver_id == myInfo->GetGithubId())
    {
        // print and save msg
        cout << "\n[!] [ "<< github_id << " ]'s Message arrived " << endl;
        data = " [+] msg > " + data;
        cout << data << endl;
        this->SaveFile(github_id, data);
    }

    // not my msg, forward it
    else
    {
        // forward to next peer
        string nextIp = UserInfoMap[receiver_id]->GetIpAddr();
        if(this->Forward(nextIp, data) < 0)
            cout << "[Error!] Fail to forward msg" << endl;
    }
    return 1;
}

int MsgServer::Forward(string ip, string msg)
{
    // forwarding msg to next ip
    int rv;
    TCPSocket* sock = new TCPSocket();
    if(!sock->Valid()) return -1;
    rv = sock->Connect(ip, SERVER_SOCK);
    if (rv < 0) return -1;
    rv = sock->Send(msg);
    delete sock;
    return rv;
}

MsgServer::~MsgServer()
{
}

