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

using namespace std;

extern UserInfo* myInfo;
extern unordered_map<string, UserInfo*> UserInfoMap;

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
        array <string,100> node_list;

        bool CheckReceiver();
        bool SetRoute();

        int SendMsg();
        int SendData();

        int EncryptMsg(string data);
};

#endif // MESSAGECLIENT_H
