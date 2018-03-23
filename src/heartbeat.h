#ifndef HEARTBEAT_H
#define HEARTBEAT_H

#include <iostream>
#include <cstring>
#include <thread>
#include <chrono>
#include <unistd.h>

#include "config.h"
#include "socket.h"

class Heartbeat
{
    public:
        Heartbeat();
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
