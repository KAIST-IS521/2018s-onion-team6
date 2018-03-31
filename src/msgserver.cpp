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
    // Create socket and listen
    p_server_sock = new ServerSocket(SERVER_SOCK);
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
    serv_addr.sin_port = htons(SERVER_SOCK);

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

    // add data
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
        string pgp_data;

        reader->parse(msg.c_str(), msg.c_str()+msg.length(), &root, &errs);
        if(errs.find("error") != string::npos)
        {
            cout << "[Error!] Not JSON Format" << endl;
            return 0;
        }
        Json::Value j_sender    = root["sender"];
        Json::Value j_receiver  = root["receiver"];
        Json::Value j_data      = root["data"];
        if(j_sender.isNull() || j_receiver.isNull() || j_data.isNull())
        {
            cout << "[Error!] Invalid Json Fromat" << endl;
            return 0;
        }
        github_id    = j_sender.asCString();
        receiver_id  = j_receiver.asCString();
        pgp_data     = j_data.asCString();

        if(receiver_id == myInfo->GetGithubId())
        {
            cout << "[!] [ "<< github_id << " ]'s Message arrived " << endl;
            pgp_data = " [+] msg > " + pgp_data;
            cout << pgp_data << endl;
            this->SaveFile(github_id,pgp_data);
        }
        // NOT MY MESSAGE
        else
        {
            string nextIp = UserInfoMap[receiver_id]->GetIpAddr();
            this->MsgClient(nextIp,pgp_data);
        }
    return 1;

}
string MsgServer::PGPDecrypt(string msg)
{
    return pgpmanager->DecryptData(msg);
}

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

