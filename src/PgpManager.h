
#ifndef PGP_MANAGER_H
#define PGP_MANAGER_H

#include <cerrno>
#include <cstdio>
#include <unistd.h>
#include <cstdlib>
#include <sys/wait.h>
#include <iostream>
#include <cstring>
#include <fstream>

#include "user_info.h"

using namespace std;
extern UserInfo * myInfo;


class PgpManager
{
public:
    PgpManager(string passwd);
    ~PgpManager();

    string EncryptData(string sender, string  pubKey, string data);
    string DecryptData(string dst);

    string RecvKey(string pubKey);
    string EditKey(char* key);


private:
    int nbytes; // For pipe reading
    string passphrase;
    string pub_key;
    void Authentication();
    string ImportMyPrivateKey();
    string CallLocalGPG(string cmdData);
    string readFile(string sender);
    string saveFile(string sender, string data);
};



#endif //PGP_MANAGER_H
