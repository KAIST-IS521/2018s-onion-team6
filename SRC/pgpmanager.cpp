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
        string pub_key_id = ret.substr((ret.find(keys))+keys.length(),8);
        myInfo->SetPGPKeyId(pub_key_id);
        SendKey(pub_key_id);
    }
    return ret;
}

string PgpManager::SendKey(string pub_key_id)
{
    // execute recv key command
    string cmd_data = "/usr/bin/gpg --keyserver keyserver.ubuntu.com";
    cmd_data += " --send-keys " + pub_key_id;
    return CallLocalGPG(cmd_data);
}

string PgpManager::RecvKey(string pub_key_id)
{
    // execute recv key command
    string cmd_data = "/usr/bin/gpg --keyserver keyserver.ubuntu.com";
    cmd_data += " --recv-keys " + pub_key_id;
    return CallLocalGPG(cmd_data);
}

std::string ReplaceAll(std::string &str, const std::string& from, const std::string& to)
{
    size_t start_pos = 0; //string처음부터 검사
    while((start_pos = str.find(from, start_pos)) != std::string::npos)  //from을 찾을 수 없을 때까지
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // 중복검사를 피하고 from.length() > to.length()인 경우를 위해서
    }
    return str;
}


string PgpManager::DecryptData(string data)
{
    // set random file name
    srand(time(NULL));
    string src = std::to_string(rand() % 100000000);
    string file_name = this->SaveFile(src, data);

    // Passphrase is plain text without filtering
    // So command injection is possible
    // And Logically, it is not possible to process special characters.(e.g. !, @)
    // execute decrypt command
    string cmd_data = "";
    string test = "";
    if( (this->passphrase.find("'", 0)) == std::string::npos ){
        test = ReplaceAll(this->passphrase, std::string("\\"), std::string("\\\\"));
        test = ReplaceAll(test, std::string("'"), std::string("\'"));
        cmd_data += "echo '" + test + "' | ";
    }
    else{
        test = this->passphrase;
        test = ReplaceAll(test, std::string("\\"), std::string("\\\\"));
        string test = ReplaceAll(this->passphrase, std::string("\""), std::string("\\\""));
        cmd_data += "echo \"" + test + "\" | ";
    }
    cmd_data += "/usr/bin/gpg --batch --yes";
    cmd_data += " --passphrase-fd 0 ";
    cmd_data += " --output " + file_name;
    cmd_data += " --decrypt " + file_name;
    CallLocalGPG(cmd_data);

    // return decrypt result
    return this->ReadFile(file_name);
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
    ofstream write_file(file_path.data());
    if(write_file.is_open())
    {
        write_file << data;
        write_file.close();
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
    ifstream open_file(file_path.data());
    if(open_file.is_open())
    {
        string data = "";
        string line;
        while(getline(open_file, line))
        {
            data += line;
            data += "\n";
        }
        open_file.close();
        return data;
    }
    else
    {
        cout << "[Error!] File open error " << file_path << endl;
        cout << "[Error!] Something problem in encrypt data." << endl;
        return "";
    }
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
