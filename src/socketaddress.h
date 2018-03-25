#ifndef SOCKETADDRESS_H
#define SOCKETADDRESS_H

#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include<iostream>

using namespace std;

class SocketAddress
{
protected:
        int port;
        std::string address;

    public:
        SocketAddress();
        SocketAddress(struct sockaddr_in addr);
        SocketAddress(std::string address, int port);
        struct sockaddr_in get_struct();
        int get_port();
        std::string get_address();
};

#endif // SOCKETADDRESS_H
