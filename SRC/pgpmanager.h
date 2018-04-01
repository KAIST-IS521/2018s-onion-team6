#ifndef PGPMANAGER_H
#define PGPMANAGER_H

#include <cerrno>
#include <cstdio>
#include <unistd.h>
#include <cstdlib>
#include <sys/wait.h>
#include <iostream>
#include <cstring>
#include <fstream>
#include <regex>

#include "user_info.h"
#include "config.h"

using namespace std;
extern UserInfo * myInfo;

class PgpManager
{
    public:
        PgpManager(string passwd);
        ~PgpManager();

        string RecvKey(string pub_key_id);
        string EncryptData(string pub_key, string data);
        string DecryptData(string dst);

    private:
        int nbytes; // for pipe reading
        string passphrase;
        string pub_key;

        bool Authentication();
        string SendKey(string pub_key_id);
        string ImportMyPrivateKey();
        string CallLocalGPG(string cmd_data);
        string ReadFile(string file_name);
        string SaveFile(string file_name, string data);
        int HackDetector(string str);
};

#endif //PGPMANAGER_H
