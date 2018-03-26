#include<iostream>
#include "onion_messenger.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout << "[D] TEST START MAIN "<< endl;
    OnionMessenger *messenger = new OnionMessenger();
    messenger->StartApp();
}
