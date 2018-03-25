#ifndef MSGCLIENT_H
#define MSGCLIENT_H

#include <iostream>
#include <unordered_map>
#include <list>

#include "json/json.h"
#include "user_info.h"
#include "socket.h"

using namespace std;

extern UserInfo* myInfo;
extern unordered_map<string, UserInfo*> UserInfoMap;

class MsgClient
{
private:
    string receiver;
    string msg;
    list<string> node_list;
    TCPSocket* send_sock;

public:
    MsgClient(string receiver, string msg);
    void Start();
    bool CheckReceiver();
    void SetRoute();
    int SendMsg();
    int SendLength();
    int SendData();
    int EncryptMsg(string data);

};

#endif // MESSAGECLIENT_H
