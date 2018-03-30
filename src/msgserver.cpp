#include "msgserver.h"


MsgServer::MsgServer()
{

}
int MsgServer::MsgClient(string ip, string msg)
{

    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        cout << "Socket creation error" <<endl;
        return -1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8888);

    if(inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr)<=0)
    {
        cout << "ERROR" << endl;
        close(sock);
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        cout << "Connect Failed" << endl;
        return -1;
    }
    else
    {
        send(sock , msg.c_str() , msg.length() , 0 );
        close(sock);
    }
return 1;
}
void MsgServer::Start()
{
   std::thread serverRun([this] { RecvServer();});
   serverRun.detach();
}
void MsgServer::RecvServer()
{
    p_server_sock = new ServerSocket(8888);
    int err = p_server_sock->listen();
    if (err != 0)
    {
        std::cout << strerror(err) << std::endl;
        exit(err);
    }

    while (true)
    {
        p_client_sock = p_server_sock->accept();
        if (!p_client_sock->valid())
        {
            delete p_client_sock;
            continue;
        }
        std::thread acceptRun([this] { Worker(p_client_sock);});
        acceptRun.detach();

    }

    delete p_server_sock;
}
string MsgServer::saveFile(string gitId, string data)
{
    string fileName=gitId;
    size_t tokenlen=0;

    //directory traversal mitigation
    while( fileName.find("/") != string::npos )
    {
         tokenlen = fileName.find("/");
         fileName = fileName.substr(tokenlen+1);
    }
    string filePath = "./MSG/" + fileName;
    ofstream writeFile(filePath.data(),ios::app);
    if(writeFile.is_open())
    {
        writeFile << data << endl;
        writeFile.close();
    }
    else
    {
        cout << "[!] FILE OPEN ERROR " << gitId << endl;
        exit(0);
    }
    return filePath;
}
int MsgServer::JsonParsor(string msg)
{
        string * data = new string(msg);

        JSONCPP_STRING errs;
        Json::Value root;
        Json::CharReaderBuilder builder;
        Json::CharReader * reader = builder.newCharReader();
        string github_id;
        string receiver_id;
        string pgp_data;

        reader->parse(data[0].c_str(), data[0].c_str()+data[0].length(), &root, &errs);
        if(errs.find("error") != string::npos)
        {
            cout << "Not JSON Format" << endl;
            return 0;
        }
        Json::Value j_sender    = root["sender"];
        Json::Value j_receiver  = root["receiver"];
        Json::Value j_data      = root["data"];

        github_id    = j_sender.asCString();
        receiver_id  = j_receiver.asCString();
        pgp_data     = j_data.asCString();

        if(receiver_id == myInfo->GetGithubId())
        {
            cout << "[!] [ "<< github_id << " ]'s Message arrived " << endl;
            pgp_data = " [+] msg > " + pgp_data;
            cout << pgp_data << endl;
            this->saveFile(github_id,pgp_data);
        }
        // NOT MY MESSAGE
        else
        {
            string nextIp = UserInfoMap[receiver_id]->GetIpAddr();
            this->MsgClient(nextIp,pgp_data);
        }

    delete data;
    data = NULL;
    return 1;

}
string MsgServer::PGPDecrypt(string msg)
{
    //return msg;
    return pgpmanager->DecryptData(msg);
}
//  UserInfo* myInfo;
//  4 unordered_map<string, UserInfo*> UserInfoMap;
//
void MsgServer::Worker(ClientSocket* client_sock)
{
    SocketAddress* addr = client_sock->get_sockaddr();
    while (true)
    {
        std::string msg;
        if (client_sock->read(msg) <= 0)
        {
            break;
        }
        string decryptedMsg = this->PGPDecrypt(msg);
        if(decryptedMsg!="")
        {
            this->JsonParsor(decryptedMsg);
        }
    }
    delete client_sock;
}
MsgServer::~MsgServer()
{
}

