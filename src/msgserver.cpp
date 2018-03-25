#include "msgserver.h"

MsgServer::MsgServer()
{

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
void MsgServer::Worker(ClientSocket* client_sock)
{
    std::cout << "Got a client!" << std::endl;
    SocketAddress* addr = client_sock->get_sockaddr();
    std::cout << addr->get_address() << ":" << addr->get_port() << std::endl;
    while (true)
    {
        std::string msg;
        if (client_sock->read(msg) <= 0)
        {
            break;
        }
        std::cout << msg;
    }
    delete client_sock;
    std::cout << "Client disconnected" << std::endl;

}
