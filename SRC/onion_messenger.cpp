#include "onion_messenger.h"

UserInfo* myInfo;
unordered_map<string, UserInfo*> UserInfoMap;
PgpManager *pgpmanager;
Heartbeat *heartbeat;

OnionMessenger::OnionMessenger()
{
    // Create UserInfo for saving my information
    myInfo = new UserInfo();
}

void OnionMessenger::StartApp()
{
    // Create Messenger shell
    Shell *shell = new Shell();

    // Create Mseenger server for receive msg
    MsgServer * msgserver = new MsgServer();
    msgserver->Start();

    // Create Heartbeat for updating peer list
    heartbeat = new Heartbeat();
    heartbeat->Start();

    // Run shell
    shell->Run();
}

OnionMessenger::~OnionMessenger()
{
}
