#include "onion_messenger.h"

UserInfo* myInfo;
unordered_map<string, UserInfo*> UserInfoMap;
PgpManager *pgpmanager;
Heartbeat *heartbeat;

OnionMessenger::OnionMessenger()
{
    myInfo = new UserInfo();
}

void OnionMessenger::StartApp()
{
    Shell *shell = new Shell();
    //PGP *pgp = new PGP(shell->GetPass());

    MsgServer * msgserver = new MsgServer();
    msgserver->Start();

    heartbeat = new Heartbeat();
    heartbeat->Start();

    shell->Run();
}

OnionMessenger::~OnionMessenger()
{
}
