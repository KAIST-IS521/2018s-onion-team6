#ifndef ONION_MESSENGER_H
#define ONION_MESSENGER_H

#include <iostream>
#include <unordered_map>

#include "msgserver.h"
#include "shell.h"
#include "heartbeat.h"
#include "pgpmanager.h"

using namespace std;

class OnionMessenger
{
    public:
        OnionMessenger();
        ~OnionMessenger();
        void StartApp();

    private:
        Heartbeat *heartbeat;
};

#endif // ONION_MESSENGER_H
