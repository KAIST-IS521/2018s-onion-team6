#ifndef HEARTBEAT_H
#define HEARTBEAT_H

#include <iostream>
#include <cstring>
#include <thread>
#include <chrono>
#include <unistd.h>
#include <unordered_map>
#include <regex>

#include "json/json.h"
#include "config.h"
#include "socket.h"
#include "user_info.h"
#include "pgpmanager.h"

using namespace std;

extern UserInfo* myInfo;
extern unordered_map<string, UserInfo*> UserInfoMap;
extern PgpManager* pgpmanager;

class Heartbeat
{
    public:
        Heartbeat();
        ~Heartbeat();

        void Start();
        void SendKill();

    private:
        void SendBroadcast();
        void RecvBroadcast();
        int HackDetector(string str);
};

#endif // HEARTBEAT_H
