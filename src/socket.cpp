#include "socket.h"

Socket::Socket()
{

}

Socket::~Socket()
{

}

int Socket::SetSockOpt(int level, int optname, const void *optval, socklen_t optlen)
{
}

int Socket::Bind(int port)
{
}

UDPSocket::UDPSocket()
{

UDPSocket::~UDPSocket()
{
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
}

TCPSocket::~TCPSocket()
{
}

int TCPSocket::Send(char* data, size_t len)
{
}

int TCPSocket::Recv(size_t len)
}

