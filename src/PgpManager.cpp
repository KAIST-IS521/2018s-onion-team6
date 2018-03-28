#include "./PgpManager.h"

PgpManager::~PgpManager() {}
PgpManager::PgpManager(string passwd)
{
    passphrase = passwd;

    ImportMyPrivateKey();
    string aaaa="aaaa";
    //getKeyList();

    //EncryptData("test.txt", "c6140206");
    //cout << "encrypt done" << endl;
    //DecryptData("test.txt.gpg", "decryptedData.txt");
    //cout << "decrypt done" << endl;

}


string PgpManager::ImportMyPrivateKey()
{

    char* argv[] = { (char *)"gpg",(char *)"--import", (char *)"private.key",NULL};
    string result_str = CallLocalGPG(argv);
    if(result_str.find("no valid OpenPGP data found") != string::npos)
    {
        cout << "[!] PRIVATE KEY IS NOT VALID" << endl;
        exit(0);

    }
    else
    {
        string keys="gpg: key ";
        cout << "[D1]" << result_str.substr((result_str.find(keys))+keys.length(),8) << endl;
    }
    return result_str;

}

string PgpManager::EditKey(char* key)
{
       char* argv[] = {
        (char *)"gpg",
        (char *)"--edit-key",
        (char *)key,
        NULL
       };
       return CallLocalGPG(argv);
}

string PgpManager::RecvKey(char* pubKey)
{
    char* argv[] = {
        (char *)"gpg",
        (char *)"--keyserver",
        (char *)"keyserver.ubuntu.com",
        (char *)"--recv-keys",
        (char *)pubKey,
        NULL
    };
    return CallLocalGPG(argv);
}

string PgpManager::AddPubkey(char* pubKey){

    // recv & save to userInfo
       RecvKey(pubKey);
    //adding this key to userinfo class is needed

       return "";
}

string PgpManager::getKeyList(){

    char* argv[] = {
        (char *)"gpg",
        (char *)"--list-keys",
        NULL
    };
    return CallLocalGPG(argv);
    /*
       printf("Output : (%.*s)\n", nbytes, DisplayedBuf);
     */

}

string PgpManager::DecryptData(char* src, char* dst){
    char* argv[]={
        (char *)"gpg",
        (char *)"--yes",
        (char *)"--passphrase",
        (char *)this->passphrase.c_str(),
        (char *)"-o",
        (char *)dst,
        (char *)"--decrypt",
        (char *)src,
        NULL
    };

    return CallLocalGPG(argv);

}


string PgpManager::EncryptData(char* srcFilename, char* pubKeyID){

    //gpg  --yes -r c6140206 --encrypt-files test.txt
    string TAG = "ENCRYPT";
    char* argv[]={
        (char *)"gpg",
        (char *)"--yes",
        (char *)"-r",
        (char *)pubKeyID,
        (char *)"--encrypt-files",
        (char *)srcFilename,
        NULL
    };
    return CallLocalGPG(argv);
}


string PgpManager::CallLocalGPG(char* const argv[])
{
    int link[2];
    char displaybuff[4096+1];
    memset(displaybuff,0,4096);

    pid_t pid;

    pipe(link);                 // error handling needed
    pid = fork();               // error hadnling needed

    if (pid == 0)
    {
        dup2(link[1], STDOUT_FILENO);
        dup2(link[1], STDERR_FILENO);
        close(link[0]);
        close(link[1]);
        execv((char *)"/usr/bin/gpg", argv);
    }

    else
    {
        int status;
        pid_t mChild = wait(&status);
        close(link[1]);
        int nbytes = read(link[0], displaybuff, 4096);
        setbuf(stdin,NULL);
        setbuf(stdout,NULL);
    }

    return (string)displaybuff;
}


void
PgpManager::Authentication(){

    string TAG = "Authentication";
    // auth file path handling needed
   // EncryptData("auth",
}

