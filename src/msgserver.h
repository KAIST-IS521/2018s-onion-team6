#ifndef MSGSERVER_H
#define MSGSERVER_H

#include<iostream>
#include<cstdlib>
#include <cstring>
#include <thread>

#include "serversocket.h"
#include "clientsocket.h"

class MsgServer
{
public:
    MsgServer();
    ~MsgServer();
    void RecvServer();
    void Start();
    void Worker(ClientSocket* client_sock);

private:
    ClientSocket * p_client_sock;
    ServerSocket * p_server_sock;
};

#endif // MSGSERVER_H
