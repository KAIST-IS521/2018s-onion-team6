#ifndef MSGCLIENT_H
#define MSGCLIENT_H

#include <iostream>
#include <unordered_map>
#include <list>
#include <stdlib.h>
#include <cstdlib>
#include "user_info.h"
//#include <algorithm>    // std::random_shuffle
//#include <vector>       // std::vector
#include <ctime>        // std::time

using namespace std;

extern UserInfo* myInfo;
extern unordered_map<string, UserInfo*> UserInfoMap;

class MsgClient
{
private:
    string receiver;
    string msg;
    array <string,100> node_list;

public:
    MsgClient(string receiver, string msg);
    void Start();
    bool CheckReceiver();
    int SetRoute();
    int SendMessage();
    int randFunc(int n);
};

#endif // MESSAGECLIENT_H
