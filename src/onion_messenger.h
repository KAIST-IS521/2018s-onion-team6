#ifndef ONION_MESSENGER_H
#define ONION_MESSENGER_H

#include <iostream>
#include <map>

#include "shell.h"
#include "heartbeat.h"
#include "user_info.h"

using namespace std;

class OnionMessenger
{
public:
    map<string, UserInfo>* UserInfoMap;

    OnionMessenger();
    ~OnionMessenger();
    void StartApp();

private:
    // Login()
    // Initialize()
};

#endif // ONION_MESSENGER_H
