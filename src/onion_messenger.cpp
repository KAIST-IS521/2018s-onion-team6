#include "onion_messenger.h"

UserInfo* myInfo;
unordered_map<string, UserInfo*> UserInfoMap;

OnionMessenger::OnionMessenger()
{
    myInfo = new UserInfo();
}

void OnionMessenger::StartApp()
{
    Shell *sha = new Shell();
    // Check passphrase
    Heartbeat *heartbeat = new Heartbeat();
    heartbeat->Start();
    sha->run();
}
