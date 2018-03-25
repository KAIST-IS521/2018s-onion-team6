#ifndef MSGCLIENT_H
#define MSGCLIENT_H

#include <iostream>
#include <unordered_map>
#include <list>

#include "user_info.h"

using namespace std;

extern UserInfo* myInfo;
extern unordered_map<string, UserInfo*> UserInfoMap;

class MsgClient
{
private:
    string receiver;
    string msg;
    list<string> node_list;

public:
    MsgClient(string receiver, string msg);
    void Start();
    bool CheckReceiver();
    void SetRoute();
    int SendMessage();

};

#endif // MESSAGECLIENT_H
