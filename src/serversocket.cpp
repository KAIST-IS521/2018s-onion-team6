#include "serversocket.h"
<<<<<<< HEAD
/*
serversocket::serversocket()
{

}
*/
serversocket::~serversocket()
{
    close();
}

int serversocket::listen()
{

    socketaddress* sockaddr = new socketaddress(address, port);
=======

ServerSocket::ServerSocket()
{

}
ServerSocket::ServerSocket(int port)
{
    this->port = port;
    backlog = 10;
    address = "0.0.0.0";
}
ServerSocket::ServerSocket(int port, int backlog)
{
    this->port = port;
    this->backlog = backlog;
    address = "0.0.0.0";
}
ServerSocket::ServerSocket(int port, int backlog, std::string address)
{
    this->port = port;
    this->backlog = backlog;
    this->address = address;
}
ServerSocket::~ServerSocket()
{
    close();
}
int ServerSocket::listen()
{

    SocketAddress* sockaddr = new SocketAddress(address, port);
>>>>>>> bbeb5875831d01fb0e3ab16dd0439d37f64f5a4d
    struct sockaddr_in addr = sockaddr->get_struct();

    sock_fd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (sock_fd == -1)
    {
        return errno;
    }

    int yes = 1;
    if (::setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) != 0)
    {
        close();
        return errno;
    }

    if (::bind(sock_fd, (struct sockaddr*)&addr, sizeof(struct sockaddr)) != 0)
    {
        close();
        return errno;
    }

    if (::listen(sock_fd, backlog) != 0)
    {
        close();
        return errno;
    }

    return 0;
}
<<<<<<< HEAD

clientsocket* serversocket::accept()
=======
ClientSocket* ServerSocket::accept()
>>>>>>> bbeb5875831d01fb0e3ab16dd0439d37f64f5a4d
{
    struct sockaddr_in from;
    socklen_t l = sizeof(from);
    int clientfd = ::accept(sock_fd, (struct sockaddr*)&from, &l);

<<<<<<< HEAD
    return new clientsocket(clientfd, from);
=======
    return new ClientSocket(clientfd, from);
}

void ServerSocket::close()
{
    if (sock_fd == -1)
    {
        return;
    }
       ::close(sock_fd);
}

bool ServerSocket::valid()
{
    return sock_fd != -1;
}

int ServerSocket::get_socket()
{
    return sock_fd;
>>>>>>> bbeb5875831d01fb0e3ab16dd0439d37f64f5a4d
}
