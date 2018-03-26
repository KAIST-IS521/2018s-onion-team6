#ifndef SOCKET_H
#define SOCKET_H

#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<cstring>
#include<iostream>

#include "config.h"

using namespace std;

class Socket
{
    public:
        Socket();
        ~Socket();

        int SetSockOpt(int level, int optname, const void *optval, socklen_t optlen);
        int Bind(int port);
        int Connect(string ip_addr);

    protected:
        int sd;
};

class UDPSocket : public Socket
{
    public:
        UDPSocket();
        virtual ~UDPSocket();

        void SetDestAddr(const char* dest_addr, int port);
        int Send(string data);
        string* Recv();

    private:
        struct sockaddr_in recvaddr;
};

class TCPSocket : public Socket
{
    public:
        TCPSocket();
        virtual ~TCPSocket();

        int Send(string data);
        int Recv(size_t len);
};

#endif // SOCKET_H
