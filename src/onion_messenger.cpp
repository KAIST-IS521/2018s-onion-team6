#include "onion_messenger.h"

UserInfo* myInfo;
unordered_map<string, UserInfo*> UserInfoMap;

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

<<<<<<< HEAD
    // Shell *sha = new Shell(id,pw);
=======
>>>>>>> bbeb5875831d01fb0e3ab16dd0439d37f64f5a4d
    Heartbeat *heartbeat = new Heartbeat();
    heartbeat->Start();


    shell->run();
}
