#include "socket.h"

Socket::Socket()
{

}

Socket::~Socket()
{

}

int Socket::SetSockOpt(int level, int optname, const void *optval, socklen_t optlen)
{
	int rv = setsockopt(this->sd, level, optname, optval, optlen);
    if (rv == -1)
    {
        perror("setsockopt");
        exit(-1);
    }
    return rv;
}
}

int Socket::Bind(int port)
{
}

UDPSocket::UDPSocket()
{
	int sd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sd < 0)
    {
        perror("socket");
        exit(-1);
    }
    this->sd = sd;
}

UDPSocket::~UDPSocket()
{
	close(this->sd);
}

void UDPSocket::SetDestAddr(char* dest_addr, int port)
{
}

int UDPSocket::Send(char* data, size_t len)
{
}

int UDPSocket::Recv(size_t len)
{
}

TCPSocket::TCPSocket()
{
	int sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd < 0)
    {
        perror("socket");
        exit(-1);
    }
    this->sd = sd;
}

TCPSocket::~TCPSocket()
{
	close(this->sd);
}

int TCPSocket::Send(char* data, size_t len)
{
}

int TCPSocket::Recv(size_t len)
}

