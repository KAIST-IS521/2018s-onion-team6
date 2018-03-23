#ifndef PGP_WRAPPER_H
#define PGP_WRAPPER_H

#include <cerrno>
#include <cstdio>
#include <string>
#include <unistd.h>
#include <cstdlib>


using namespace std;

#define DEBUG_FLAG 1
#define DEBUG if(DEBUG_FLAG)

#define PROPER_GPG  1111
#define INVALID_GPG  0000

#define MAX_DISPLAY_BUF 4096
#define MAX_ONE_LINE 4096
#define NUM_OF_COMMANDS 

#define GPG_PATH  "/usr/bin/gpg" 
#define GPG_COMMAND "gpg"

class PgpWrapper
{
    public:
        PgpWrapper();
        PgpWrapper(const string pubKey);
        ~PgpWrapper();

        int CheckProperGPG();
        
        int EncryptData(FILE* srcFile, string pubKey[64]);   // Handle files to send
        int EncryptData(string srcStr, string pubKey[64]);   // Handle msgs to send

        int DecryptData(FILE* inFile);      // Handle file from peer
        int DecryptData(string inSrc);      // Handle msgs from peer

        void ImportMyPrivateKey();         // importing node's private key
   

    private:
    //   const int PROPER_GPG = 1111;
     //  const int INVALID_GPG = 0;
      // const  char* GPG_PATH = "/usr/bin/gpg";
      // const  char* GPG_COMMAND= "gpg";

};



#endif //PGP_WRAPPER_H
