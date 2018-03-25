#ifndef ONION_MESSENGER_H
#define ONION_MESSENGER_H

#include <iostream>
#include <unordered_map>

#include "user_info.h"
#include "shell.h"
#include "heartbeat.h"
#include "pgp.h"

using namespace std;

class OnionMessenger
{
    public:
        OnionMessenger();
        ~OnionMessenger();
        void StartApp();

    private:
};

#endif // ONION_MESSENGER_H
