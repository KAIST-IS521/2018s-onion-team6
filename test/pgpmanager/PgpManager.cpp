#include "./PgpManager.h"
#include <iostream>
using namespace std;


enum {
	GET_GPG_VERSION = 0,
	IMPORT_PRIVATE_KEY,
    GET_LIST_KEYS
};

char* const  MY_GPG_OPTION[] = {
	"--version",
	"--import",
    "--list-keys"
};



PgpManager::~PgpManager() {}

PgpManager::PgpManager() {
	if (CheckProperGPG()) cout << "PROPER_GPG" << endl;              // proper handling needed
	else cout << "INVALID_GPG" << endl;

	ImportMyPrivateKey(PRIVATE_KEY);
    getKeyList();


}

PgpManager::PgpManager(char* PubKey) {
	PgpManager();
}

int
PgpManager::ImportMyPrivateKey(char*  privKey) {

    string TAG = "ImportMyPrivateKey";
   char* argv[] = {
        GPG_COMMAND, 
        MY_GPG_OPTION[IMPORT_PRIVATE_KEY],
        privKey,
        NULL
    };
	CallLocalGPG(TAG,argv);



}


void
PgpManager::getKeyList(){

    string TAG = "getKeyList";
    char* argv[] = {
        GPG_COMMAND,
        MY_GPG_OPTION[GET_LIST_KEYS],
        NULL
    };
    CallLocalGPG(TAG, argv);
    /*
    printf("Output : (%.*s)\n", nbytes, DisplayedBuf);
    */

}


void
PgpManager::CleanDisplayedBuf() {
	for (int i = 0; i<MAX_DISPLAY_BUF; i++)DisplayedBuf[i] = '\0';
    nbytes = 0;
}


void
PgpManager::CallLocalGPG(string msg, char* const argv[])
{
	DEBUG cout << msg + "start!!" << endl;
	int link[2];
	CleanDisplayedBuf();
	//int pid;
	pid_t pid;


	pipe(link);                 // error handling needed
	pid = fork();               // error hadnling needed

	if (pid == 0) {
        /*
        DEBUG{
            cout << argv[0] << endl;
            cout << argv[1] << endl;;
            cout << argv[2] << endl;
        }
        */


		dup2(link[1], STDOUT_FILENO);
		close(link[0]);
		close(link[1]);


		
       execv(GPG_PATH, argv );

	//	 execl(GPG_PATH, "gpg", cmd_option ,(char*) 0);
	}

	else {
		close(link[1]);

		int nbytes = read(link[0], DisplayedBuf, MAX_DISPLAY_BUF);
		DEBUG  printf("Output : (%.*s)\n", nbytes, DisplayedBuf);       // parsing needed
       
	}

}

int
PgpManager::CheckProperGPG() {
   
    string TAG = "CheckerProperGPG";
    char* argv[] = {
        GPG_COMMAND,
        MY_GPG_OPTION[GET_GPG_VERSION],
            NULL
    };


	CallLocalGPG(TAG, argv);

	char sig[11];
	for (int i = 0; i<10; i++) sig[i] = DisplayedBuf[i];
	sig[10] = '\0';
	string mSig = sig;


    DEBUG printf("Output : (%.*s)\n", MAX_DISPLAY_BUF, DisplayedBuf);
	if (mSig.find("(GnuPG") != string::npos) {

		return PROPER_GPG;
	}


	return INVALID_GPG;


}




