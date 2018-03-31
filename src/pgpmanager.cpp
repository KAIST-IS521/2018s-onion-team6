#include "pgpmanager.h"

PgpManager::~PgpManager() {}
PgpManager::PgpManager(string passwd)
{
    // import privat key and check passphrase
    passphrase = passwd;
    ImportMyPrivateKey();
    if(!Authentication())
    {
        exit(0);
    }
}

string PgpManager::ImportMyPrivateKey()
{
    // execute import command
    string cmd_data = "/usr/bin/gpg --import private.key";
    string ret = CallLocalGPG(cmd_data);

    // check result
    if(ret.find("no valid OpenPGP data found") != string::npos)
    {
        cout << "[Error!] private.key is not valid" << endl;
        exit(0);
    }
    else
    {
        // get pgp key id
        string keys="gpg: key ";
        string key_id = ret.substr((ret.find(keys))+keys.length(),8);
        myInfo->SetPGPKeyId(key_id);
    }
    return ret;
}

string PgpManager::RecvKey(string pub_key_id)
{
    // execute recv key command
    string cmdData = "/usr/bin/gpg --keyserver keyserver.ubuntu.com";
    cmdData += " --recv-keys " + pub_key_id;
    return CallLocalGPG(cmdData);
}

string PgpManager::DecryptData(string data)
{
    // set random file name
    srand(time(NULL));
    string src = std::to_string(rand() % 100000000);
    string file_name = this->saveFile(src, data);

    // execute decrypt command
    string cmdData = "/usr/bin/gpg --batch --yes";
    cmdData += " --passphrase \"" + this->passphrase;
    cmdData += "\" --output " + fileName;
    cmdData += " --decrypt " + fileName;
    CallLocalGPG(cmdData);

    // return decrypt result
    return this->readFile(file_name);
}

string PgpManager::SaveFile(string file_name, string data)
{
    size_t tokenlen=0;

    // directory traversal mitigation
    while( file_name.find("/") != string::npos )
    {
        tokenlen = file_name.find("/");
        file_name = file_name.substr(tokenlen+1);
    }
    string file_path = "./MEMBER/" + file_name;

    // open file and write data
    ofstream writeFile(file_path.data());
    if(writeFile.is_open())
    {
        writeFile << data;
        writeFile.close();
    }
    else
    {
        cout << "[Error!] File open error " << file_path << endl;
        exit(0);
    }
    return file_path;
}

string PgpManager::ReadFile(string file_name)
{
    size_t tokenlen=0;

    // directory traversal mitigation
    while( file_name.find("/") != string::npos )
    {
        tokenlen = file_name.find("/");
        file_name = file_name.substr(tokenlen+1);
    }
    string file_path = "./MEMBER/" + file_name;

    // open file and read data
    ifstream openFile(filePath.data());
    if(openFile.is_open())
    {
        string data = "";
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
        cout << "[Error!] File open error " << file_path << endl;
        exit(0);
    }
    return "";
}

string PgpManager::EncryptData(string pub_key_id, string data)
{
    // Set file name randomly
    string src = std::to_string(rand() % 100000000);
    string file_name = this->SaveFile(src, data);

    // Execute encrypt command
    string cmd_data = "/usr/bin/gpg --batch --yes --always-trust --armor";
    cmd_data += " -r " + pub_key_id + " --encrypt-files " +file_name;
    string result =  CallLocalGPG(cmd_data);

    // if fails decrypt, recv receiver's pub key from keyserver
    if(result.find("public key not found") != string::npos){
            RecvKey(pub_key_id);
            CallLocalGPG(cmd_data);
    }
    return this->ReadFile(file_name + ".asc");
}

string PgpManager::CallLocalGPG(string cmd_data)
{
    cmd_data += " 2>&1";    // redirect stderr to stdout

    string data; // popen result
    char buff[BUFF_SIZE]; // popen buffer
    memset(buff, 0, BUFF_SIZE);

    // execute command
    FILE * stream = popen(cmd_data.c_str(),"r");
    if(stream)
    {
        while(!feof(stream))
        {
            // read command result
            if(fgets(buff, BUFF_SIZE, stream) != NULL)
            {
                data.append(buff);
            }
            memset(buff, 0, BUFF_SIZE);
        }
        pclose(stream);
    }
    return data;
}

bool PgpManager::Authentication()
{
    // encrypt data using my pgp key id and decrypt again for checking passphrase
    if(DecryptData(EncryptData(myInfo->GetPGPKeyId(),"CLEAR")).find("CLEAR")!= string::npos)
    {
        return true;
    }
    else
    {
        cout << "[Error!] Passphrase is not matched" <<endl;
        return false;
    }
}
