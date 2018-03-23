#include "onion_messenger.h"

using namespace std;
OnionMessenger::OnionMessenger()
{
    myInfo = new UserInfo();
}

void OnionMessenger::StartApp()
{

    Shell *sha = new Shell();
    // Check passphrase
    Heartbeat *heartbeat = new Heartbeat(this->UserInfoMap);
    heartbeat->Start();
    sha->run();
}
