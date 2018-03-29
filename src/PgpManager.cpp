#include "./PgpManager.h"

PgpManager::~PgpManager() {}
PgpManager::PgpManager(string passwd)
{
    passphrase = passwd;
    ImportMyPrivateKey();
}


string PgpManager::ImportMyPrivateKey()
{
    string cmdData = "/usr/bin/gpg --import private.key";

    string ret = CallLocalGPG(cmdData);

    cout <<"[D3] pgpmanager end"<<endl;
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

string PgpManager::RecvKey(string pubKey_id)
{
    string cmdData = "/usr/bin/gpg --keyserver keyserver.ubuntu.com";
    cmdData += " --recv-keys " + pubKey_id;
    return CallLocalGPG(cmdData);
}

string PgpManager::DecryptData(string data)
{
    srand(time(NULL));
    string src = std::to_string(rand() % 100000000);
    string fileName = this->saveFile(src,data);
    string cmdData = "/usr/bin/gpg --batch --yes";
    cmdData += " --passphrase " + this->passphrase;
    cmdData += " --output " + fileName;
    cmdData += " --decrypt " + fileName;

    CallLocalGPG(cmdData);
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
    return filePath;
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
            data += "\n";
        }
        openFile.close();
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
    string cmdData = "/usr/bin/gpg --batch --yes --always-trust --armor";
    cmdData += " -r " + pubKeyID + " --encrypt-files " +fileName;
    CallLocalGPG(cmdData);
    return this->readFile(fileName+".asc");

}


string PgpManager::CallLocalGPG(string cmdData)
{
    cout << "[D]Pgp callLocalGPG " << cmdData;
    cmdData += " 2>&1";
    string data;
    string line;
    char buff[4096];
    FILE * stream1 = popen(cmdData.c_str(),"r");
    memset(buff,0,4096);
    if(stream1)
    {

        while(!feof(stream1))
        {
            if(fgets(buff,4096,stream1)!=NULL)
            {
                data.append(buff);
                //data += "\n";
            }
            memset(buff,0,4096);
        }
        pclose(stream1);
    }
    cout << "[D2]Pgp callLocalGPG " << data;
    return data;
}


void PgpManager::Authentication()
{

    string TAG = "Authentication";
    // auth file path handling needed
   // EncryptData("auth",
}

