#include "serversocket.h"

serversocket::~serversocket()
{
    close();
}

int serversocket::listen()
{

    socketaddress* sockaddr = new socketaddress(address, port);
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

tcpsocket* serversocket::accept()
{
    struct sockaddr_in from;
    socklen_t l = sizeof(from);
    int clientfd = ::accept(sock_fd, (struct sockaddr*)&from, &l);

    return new tcpsocket(clientfd, from);
}