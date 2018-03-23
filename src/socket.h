#ifndef SOCKET_H
#define SOCKET_H

#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<cstring>
#include<iostream>

#define MAX_BUF_LEN 1024
#define MAX_SEND_LEN 1024

using namespace std;

class Socket
{
public:
    Socket();
    ~Socket();

    int SetSockOpt(int level, int optname, const void *optval, socklen_t optlen);
    int Bind(int port);

protected:
    int sd;
};

class UDPSocket : public Socket
{
public:
    UDPSocket();
    virtual ~UDPSocket();

    void SetDestAddr(char* dest_addr, int port);
    int Send(char* data, size_t len);
    int Recv(size_t len);
private:
    struct sockaddr_in _recvaddr;
};

class TCPSocket : public Socket
{
public:
    TCPSocket();
    virtual ~TCPSocket();

    int Send(char* data, size_t len);
    int Recv(size_t len);
};

#endif // SOCKET_H
