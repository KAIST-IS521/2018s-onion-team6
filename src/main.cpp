#include<iostream>
#include "onion_messenger.h"

using namespace std;

int main(int argc, char *argv[])
{
    string tmp = "";
    getline(cin,tmp);
    OnionMessenger *messenger = new OnionMessenger();
    messenger->StartApp();
}
