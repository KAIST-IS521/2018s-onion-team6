<<<<<<< HEAD
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
=======
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
>>>>>>> bbeb5875831d01fb0e3ab16dd0439d37f64f5a4d
