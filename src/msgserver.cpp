#include "msgserver.h"

MsgServer::MsgServer()
{
<<<<<<< HEAD
=======

>>>>>>> bbeb5875831d01fb0e3ab16dd0439d37f64f5a4d
}
void MsgServer::Start()
{
    std::thread serverRun([this] { RecvServer();});
<<<<<<< HEAD
    serverRun.join();
}
void MsgServer::RecvServer()
{
    p_server_sock = new serversocket(8888);
=======
    serverRun.detach();
}
void MsgServer::RecvServer()
{
    p_server_sock = new ServerSocket(8888);
>>>>>>> bbeb5875831d01fb0e3ab16dd0439d37f64f5a4d
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
<<<<<<< HEAD
        acceptRun.join();
        //std::thread myThread(&MsgServer::Worker, this);
        //myThread.join();
        //std::thread* t = new std::thread(MsgServer::Worker, p_client_sock);
}

delete p_server_sock;

}

void MsgServer::Worker(clientsocket* client_sock)
{
        std::cout << "Got a client!" << std::endl;
        socketaddress* addr = client_sock->get_sockaddr();
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


=======
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
>>>>>>> bbeb5875831d01fb0e3ab16dd0439d37f64f5a4d
