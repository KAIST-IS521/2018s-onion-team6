#ifndef HEARTBEAT_H
#define HEARTBEAT_H

#include <iostream>
#include <cstring>
#include <thread>
#include <chrono>
#include <unistd.h>
#include <map>

#include "json/json.h"
#include "config.h"
#include "socket.h"
#include "user_info.h"
#include "onion_messenger.h"

extern UserInfo * myInfo;

class Heartbeat
{
    public:
        Heartbeat(map<string, UserInfo>* UserInfoMap);
        ~Heartbeat();

        void Start();

    private:
        UDPSocket* send_sock;
        UDPSocket* recv_sock;

        int Initialize();
        int CreateSocket();
        int SetSocket();
        void SendBroadcast();
        void RecvBroadcast();
};

#endif // HEARTBEAT_H
