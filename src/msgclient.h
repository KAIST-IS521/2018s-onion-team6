#ifndef MSGCLIENT_H
#define MSGCLIENT_H

#include <iostream>
#include <unordered_map>
#include <list>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>        // std::time

#include "json/json.h"
#include "user_info.h"
#include "socket.h"
#include "user_info.h"
#include "clientsocket.h"
#include "PgpManager.h"
using namespace std;

extern UserInfo* myInfo;
extern unordered_map<string, UserInfo*> UserInfoMap;
extern PgpManager *pgpmanager;

class MsgClient
{
    public:
        MsgClient(string receiver, string msg);
        ~MsgClient();
        void Start();

    private:
        string receiver;
        string msg;
        TCPSocket* send_sock;
        array <string,110> node_list;
        int route_length;

        bool CheckReceiver();
        bool SetRoute();

        int SendMsg();
        int SendData();

        string EncryptMsg(string data);
        string GetIpAddress(string github_id);
        string GetPGPKeyId(string github_id);
};

#endif // MESSAGECLIENT_H
