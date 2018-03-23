#include "onion_messenger.h"

using namespace std;
OnionMessenger::OnionMessenger()
{

}

void OnionMessenger::StartApp()
{
    string id;
    string pw;

    cout << "INPUT ID > ";
    cin >> id;

    cout << "INPUT Pass > ";
    cin >> pw;

    // Shell *sha = new Shell(id,pw);
    Heartbeat *heartbeat = new Heartbeat();
    heartbeat->Start();

    // login
    // init
    // broadcast
    // pgp private key import
    // shell prompt
}
