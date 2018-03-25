#include<iostream>
#include "onion_messenger.h"
#include "user_info.h"


using namespace std;

UserInfo * myInfo;

int main(int argc, char *argv[])
{
    myInfo = new UserInfo();
    cout << "[D] TEST START MAIN "<< endl;
    OnionMessenger *messenger = new OnionMessenger();
    messenger->StartApp();
}
