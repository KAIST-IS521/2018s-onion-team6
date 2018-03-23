#include "onion_messenger.h"
#include "Shell.h"
#include <iostream>
using namespace std;
OnionMessenger::OnionMessenger()
{

}


void OnionMessenger::StartApp()
{

    Shell *sha = new Shell();


    sha->run();

    // login
    // init
    // broadcast
    // pgp private key import
    // shell prompt
}
