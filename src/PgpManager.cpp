#include "./PgpManager.h"

PgpManager::~PgpManager() {}
PgpManager::PgpManager(string passwd)
{
    passphrase = passwd;
    ImportMyPrivateKey();
}


string PgpManager::ImportMyPrivateKey()
{

    char* argv[] = {
        (char *)"gpg",
        (char *)"--import",
        (char *)"private.key",
        NULL
    };
    string ret = CallLocalGPG(argv);
    if(ret.find("no valid OpenPGP data found") != string::npos)
    {
        cout << "[!] PRIVATE KEY IS NOT VALID" << endl;
        exit(0);

    }
    else
    {
        string keys="gpg: key ";
        string key_id = ret.substr((ret.find(keys))+keys.length(),8);
        myInfo->SetPGPKeyId(key_id);
    }
    return ret;

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

string PgpManager::RecvKey(string pubKey_id)
{
    char* argv[] = {
        (char *)"gpg",
        (char *)"--keyserver",
        (char *)"keyserver.ubuntu.com",
        (char *)"--recv-keys",
        (char *)pubKey_id.c_str(),
        NULL
    };
    return CallLocalGPG(argv);
}

string PgpManager::DecryptData(string data)
{
    srand(time(NULL));
    string src = std::to_string(rand() % 100000000);
    string fileName = this->saveFile(src,data);
    char* argv[]={
        (char *)"gpg",
        (char *)"--batch",
        (char *)"--yes",
        (char *)"--passphrase",
        (char *)this->passphrase.c_str(),
        (char *)"--output",
        (char *)("./MEMBER/"+fileName).c_str(),
        (char *)"--decrypt",
        (char *)("./MEMBER/"+fileName).c_str(),
        NULL
    };
    CallLocalGPG(argv);
    return this->readFile(fileName);
}
string PgpManager::saveFile(string gitId, string data)
{
    string fileName=gitId;
    size_t tokenlen=0;

    //directory traversal mitigation
    while( fileName.find("/") != string::npos )
    {
         tokenlen = fileName.find("/");
         fileName = fileName.substr(tokenlen+1);
    }
    string filePath = "./MEMBER/" + fileName;
    ofstream writeFile(filePath.data());
    if(writeFile.is_open())
    {
        writeFile << data;
        writeFile.close();
    }
    else
    {
        cout << "[!] FILE OPEN ERROR " << gitId << endl;
        exit(0);
    }
    return fileName;
}
string PgpManager::readFile(string gitId)
{
    string fileName=gitId;
    size_t tokenlen=0;

    //directory traversal mitigation
    while( fileName.find("/") != string::npos )
    {
         tokenlen = fileName.find("/");
         fileName = fileName.substr(tokenlen+1);
    }
    string filePath = "./MEMBER/" + fileName;
    ifstream openFile(filePath.data());
    if(openFile.is_open())
    {
        string data="";
        string line;
        while(getline(openFile, line))
        {
            data += line;
        }
        return data;
    }
    else
    {
        cout << "[!] FILE OPEN ERROR " << filePath << endl;
        exit(0);
    }
    return "";
}
string PgpManager::EncryptData(string sender, string pubKeyID, string data)
{
    string fileName = this->saveFile(sender,data);
    char* argv[]={
        (char *)"gpg",
        (char *)"--batch",
        (char *)"--yes",
        (char *)"--always-trust",
        (char *)"--armor",
        (char *)"-r",
        (char *)pubKeyID.c_str(),
        (char *)"--encrypt-files",
        (char *)("./MEMBER/"+fileName).c_str(),
        NULL
    };
    CallLocalGPG(argv);
    return this->readFile(fileName+".asc");

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

