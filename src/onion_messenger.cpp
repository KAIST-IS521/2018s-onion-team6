#include "onion_messenger.h"

using namespace std;
OnionMessenger::OnionMessenger()
{

}

void OnionMessenger::StartApp()
{

    Shell *sha = new Shell();


<<<<<<< HEAD
    // Shell *sha = new Shell(id,pw);
    Heartbeat *heartbeat = new Heartbeat();
    heartbeat->Start();
=======
    sha->run();
>>>>>>> sangsup

    // login
    // init
    // broadcast
    // pgp private key import
    // shell prompt
}
