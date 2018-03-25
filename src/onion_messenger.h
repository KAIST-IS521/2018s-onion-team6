#ifndef ONION_MESSENGER_H
#define ONION_MESSENGER_H

#include <iostream>
#include <unordered_map>

#include "msgserver.h"
#include "shell.h"
#include "heartbeat.h"
<<<<<<< HEAD
#include "user_info.h"
#include "msgserver.h"

=======
#include "pgp.h"
>>>>>>> bbeb5875831d01fb0e3ab16dd0439d37f64f5a4d

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
