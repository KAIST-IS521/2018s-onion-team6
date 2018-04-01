#ifndef MSGSERVER_H
#define MSGSERVER_H

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <thread>
#include <unordered_map>

#include "json/json.h"
#include "config.h"
#include "serversocket.h"
#include "clientsocket.h"
#include "user_info.h"
#include "pgpmanager.h"
#include "socket.h"

extern UserInfo* myInfo;
extern unordered_map<string, UserInfo*> UserInfoMap;
extern PgpManager* pgpmanager;

class MsgServer
{
    public:
        MsgServer();
        ~MsgServer();

        void Start();

    private:
        TCPSocket* server_sock;
        TCPSocket* client_sock;

        void RecvServer();
        void Worker(TCPSocket* client_sock);
        int JsonParsor(string msg);
        string PGPDecrypt(string msg);
        string SaveFile(string id, string msg);
        int Forward(string ip, string msg);
};

#endif // MSGSERVER_H
