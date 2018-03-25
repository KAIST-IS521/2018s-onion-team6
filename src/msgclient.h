#ifndef MSGCLIENT_H
#define MSGCLIENT_H

#include <iostream>
#include <unordered_map>
#include <list>

#include "json/json.h"
#include "user_info.h"
#include "socket.h"
#include <stdlib.h>
#include <cstdlib>
#include "user_info.h"
#include <ctime>        // std::time

using namespace std;

extern UserInfo* myInfo;
extern unordered_map<string, UserInfo*> UserInfoMap;

class MsgClient
{
private:
    string receiver;
    string msg;
    TCPSocket* send_sock;
    array <string,100> node_list;

public:
    MsgClient(string receiver, string msg);
    void Start();
    bool CheckReceiver();
    int SendMsg();
    int SendLength();
    int SendData();
    int EncryptMsg(string data);
    int SetRoute();
    int SendMessage();
};

#endif // MESSAGECLIENT_H
