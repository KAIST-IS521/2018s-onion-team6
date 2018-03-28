
#ifndef PGP_MANAGER_H
#define PGP_MANAGER_H

#include <cerrno>
#include <cstdio>
#include <string>
#include <unistd.h>
#include <cstdlib>
#include <sys/wait.h>

using namespace std;

#define DEBUG_FLAG 0
#define DEBUG if(DEBUG_FLAG)

#define PROPER_GPG  1111
#define INVALID_GPG  0000

#define MAX_DISPLAY_BUF 4096
#define MAX_ONE_LINE 4096
#define NUM_OF_COMMANDS 

#define GPG_PATH  "/usr/bin/gpg" 
#define GPG_COMMAND "gpg"
#define PRIVATE_KEY "secret.asc"

class PgpManager
{
public:
	PgpManager();
	PgpManager(char* pubKey);
	~PgpManager();

	int CheckProperGPG();

    int EncryptData(FILE* srcFile, string pubKey);   // Handle files to send
	int EncryptData(char* srcFileName, char* pubKey);   // Handle msgs to send

	int DecryptData(FILE* inFile);      // Handle file from peer
	int DecryptData(char* src, char* dst);      // Handle msgs from peer

	int ImportMyPrivateKey(char* const  privKey);         // importing node's private key

	// Adding other's pubkey
    int AddPubkey(char* pubKey);
    int RecvKey(char* pubKey);
    int EditKey(char* key);
    /*
       getKeyList return values customizing needed
     */
    void getKeyList();      
    
    void CallLocalGPG(string msg, char* const argv[]);
	void CleanDisplayedBuf();

private:

	char DisplayedBuf[MAX_DISPLAY_BUF];
    int nbytes; // For pipe reading
    char MY_PASSPHRASE [128];
    char MY_PUBKEY[64];
    void Authentication();
	//   const int PROPER_GPG = 1111;
	//  const int INVALID_GPG = 0;
	// const  char* GPG_PATH = "/usr/bin/gpg";
	// const  char* GPG_COMMAND= "gpg";

};



#endif //PGP_MANAGER_H
