#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include<iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cerrno>

#include "clientsocket.h"

using namespace std;

class ServerSocket
{ 
protected:
    int port;
    int backlog;
    int sock_fd;
    std::string address;

public:
    ServerSocket();
    ServerSocket(int port);
    ServerSocket(int port, int backlog);
    ServerSocket(int port, int backlog, std::string address);
    ~ServerSocket();

    int listen();
    ClientSocket* accept();
    void close();
    bool valid();
    int get_socket();
};

#endif // SERVERSOCKET_H
