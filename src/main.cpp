#include<iostream> 
#include "onion_messenger.h"

using namespace std;
int main(int argc, char *argv[])
{
    OnionMessenger *messenger = new OnionMessenger();
    messenger->StartApp();
    cout << "TEST START MAIN "<< endl;
}
