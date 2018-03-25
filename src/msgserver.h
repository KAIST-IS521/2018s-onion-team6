#ifndef MSG_SERVER_H
#define MSG_SERVER_H

#include<iostream>
#include<cstdlib>
#include <string>

#include <cstring>
#include <thread>
#include "serversocket.h"
//#include "tcpsocket.h"
//#include "socketaddress.h"
class MsgServer
{
    public:
        MsgServer();
        ~MsgServer();
        void RecvServer();
        void Start();
        void Worker(clientsocket* client_sock);

    private:
        clientsocket * p_client_sock;
        serversocket * p_server_sock;

};


#endif
