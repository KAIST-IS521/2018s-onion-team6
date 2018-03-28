
#ifndef PGP_MANAGER_H
#define PGP_MANAGER_H

#include <cerrno>
#include <cstdio>
#include <unistd.h>
#include <cstdlib>
#include <sys/wait.h>
#include <iostream>
#include <cstring>

using namespace std;

class PgpManager
{
public:
    PgpManager(string passwd);
    ~PgpManager();

    string EncryptData(FILE* srcFile, string pubKey);   // Handle files to send
    string EncryptData(char* srcFileName, char* pubKey);   // Handle msgs to send

    string DecryptData(FILE* inFile);      // Handle file from peer
    string DecryptData(char* src, char* dst);      // Handle msgs from peer

    string ImportMyPrivateKey();         // importing node's private key

    string AddPubkey(char* pubKey);
    string RecvKey(char* pubKey);
    string EditKey(char* key);
    /*
       getKeyList return values customizing needed
     */
    string getKeyList();
    string CallLocalGPG(char* const argv[]);

private:
    int nbytes; // For pipe reading
    string passphrase;
    string pub_key;
    void Authentication();

};



#endif //PGP_MANAGER_H
