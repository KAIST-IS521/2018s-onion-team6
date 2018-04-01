#ifndef SOCKET_H
#define SOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <fcntl.h>

#include "config.h"

using namespace std;

class Socket
{
    public:
        Socket();
        ~Socket();

        bool Valid();
        int SetSockOpt(int level, int optname, const void *optval, socklen_t optlen);
        int Bind(int port);
        int Connect(string ip_addr, int port);

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
        TCPSocket(int sd);
        virtual ~TCPSocket();

        int Send(string data);
        int Recv(std::string& msg);
        TCPSocket* Accept();
        int Listen(int backlog);

    private:
        void SetBlocking();
        void SetNonblocking();
};

#endif // SOCKET_H
