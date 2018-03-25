#include "onion_messenger.h"

using namespace std;
OnionMessenger::OnionMessenger()
{

}

void OnionMessenger::StartApp()
{

    Shell *sha = new Shell();

   // MsgServer * msgserver = new MsgServer();
    //msgserver->Start();

    // Shell *sha = new Shell(id,pw);
    Heartbeat *heartbeat = new Heartbeat();
    heartbeat->Start();
    sha->run();

    // login
    // init
    // broadcast
    // pgp private key import
    // shell prompt
}
