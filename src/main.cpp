#include<iostream>
#include<csignal>
#include "onion_messenger.h"

using namespace std;

extern Heartbeat *heartbeat;

void signalHandler(int signum);

int main(int argc, char *argv[])
{
    signal(SIGINT, signalHandler);
    string tmp = "";
    getline(cin,tmp);
    OnionMessenger *messenger = new OnionMessenger();
    messenger->StartApp();
}

void signalHandler(int signum)
{
    heartbeat->SendKill();
    exit(signum);
}
