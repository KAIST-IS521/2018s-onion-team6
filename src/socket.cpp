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
	struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = port;
    memset(addr.sin_zero, '\0', sizeof addr.sin_zero);

    int rv = bind(this->sd, (struct sockaddr *) &addr, sizeof addr);
    if (rv < 0)
    {
        perror("bind");
        exit(-1);
    }
    return rv;
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
	this->_recvaddr.sin_family = AF_INET;
    this->_recvaddr.sin_addr.s_addr = inet_addr(dest_addr);
    this->_recvaddr.sin_port = port;
    memset(this->_recvaddr.sin_zero, '\0', sizeof this->_recvaddr.sin_zero);
}

int UDPSocket::Send(char* data, size_t len)
{
	int rv = sendto(this->sd, data, len, 0, (struct sockaddr*)&(this->_recvaddr), sizeof _recvaddr);
    if (rv < 0)
    {
        perror("send");
        exit(-1);
    }
    return rv;
}

int UDPSocket::Recv(size_t len)
{
	char buf[MAX_BUF_LEN];
    struct sockaddr_in src_addr;
    int addrlen = sizeof(src_addr);
    int rv = recvfrom(this->sd, buf, len, 0, (struct sockaddr*)&src_addr, (socklen_t*)&addrlen);
    if (rv < 0)
    {
        perror("send");
        exit(-1);
    }
    return rv;
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
	int rv = send(this->sd, data, len, 0);
    if (rv < 0)
    {
        perror("send");
        exit(-1);
    }
    return rv;
}

int TCPSocket::Recv(size_t len)
{
	char buf[MAX_BUF_LEN];
    int rv = recv(this->sd, buf, len, 0);
    if (rv < 0)
    {
        perror("send");
        exit(-1);
    }
    return rv;
}


