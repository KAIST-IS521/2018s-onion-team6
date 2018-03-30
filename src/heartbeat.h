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

using namespace std;

extern UserInfo* myInfo;
extern unordered_map<string, UserInfo*> UserInfoMap;

class Heartbeat
{
    public:
        Heartbeat();
        ~Heartbeat();

        void Start();
        void SendKill();

    private:
        //UDPSocket* send_sock;
        //UDPSocket* recv_sock;

        //int Initialize();
        //int CreateSocket();
        //int SetSocket();
        void SendBroadcast();
        void RecvBroadcast();
        int hackDetector(string v1);
};

#endif // HEARTBEAT_H
