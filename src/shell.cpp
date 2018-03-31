#include "shell.h"

Shell::Shell()
{
    Login();
    pgpmanager = new PgpManager(this->private_pw);
}

void Shell::Login()
{
    string s_id;
    string s_pw;

    // print banner
    cout << this->banner << endl;

    // Get user id
    cout << "[+] GIT_ID > ";
    cin >> s_id;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Get user passwd
    cout << "[+] Private key password > ";
    s_pw = GetPassword();

    // Save user info
    private_id = s_id;
    private_pw = s_pw;
    myInfo->SetGithubId(s_id);
}

void Shell::Run()
{
    // print usage and run shell
    push_list(" # ");
    usage();
    while(1) CShell();
}

void Shell::usage()
{
    cout << " USAGE : # [COMMAND]" << endl;
    cout << "           {help}                        : print usage" << endl;
    cout << "           {send} {GIT_ID}               : send message" << endl;
    cout << "                            -> {MESSAGE} : input message" << endl;
    cout << "           {ls}                          : show received message list " << endl;
    cout << "           {cat} {GIT_ID}                : print recvived message" << endl;
    cout << "           {id}                          : show my info" << endl;
    cout << "           {w}                           : show member list" << endl;
    cout << "           {exit}                        : program exit" << endl;
    cout << endl;
}

int Shell::PrintPrompt()
{
    // print shell prompt
    if(!prompt.empty())
    {
        list <string>::iterator itor;
        for(itor=prompt.begin(); itor!=prompt.end(); itor++)
            cout << *itor;
    }
    return 0;
}

int Shell::CShell()
{
    PrintPrompt();
    ParseCmd();
    return 1;
}

int Shell::ParseCmd()
{
    // get last prompt string
    list<string>::iterator iter = prompt.end();
    string shell=(*--iter);

    setbuf(stdin, NULL);
    setbuf(stdout, NULL);

    if(!shell.substr(0,3).compare(" # "))
    {
        string cmd;
        getline(cin, cmd);

        // print usage
        if(!cmd.substr(0,4).compare("help") || !cmd.substr(0,1).compare("?"))
        {
            usage();
        }

        // get message list
        else if(!cmd.substr(0,2).compare("ls"))
        {
            ls();
        }

        // view message to select
        else if (!cmd.substr(0,3).compare("cat"))
        {
            if(cmd.size() > 4)
                cat(cmd.substr(4,250)); //max path size is 255
        }

        // before exit, send kill message
        else if (!cmd.substr(0,4).compare("exit"))
        {
            heartbeat->SendKill();
            exit(0);
        }

        // show my information
        else if (!cmd.substr(0,2).compare("id"))
        {
            printMyInfo();
        }

        // show online member list
        else if (!cmd.substr(0,1).compare("w"))
        {
            printMember();
        }

        // send message to online member
        else if (!cmd.substr(0,4).compare("send"))
        {
            if(cmd.size()>5)
            {
                this->receiver = cmd.substr(5,250);
                send(this->receiver);
            }
        }

        // not defined command
        else
        {
            usage();
        }
    }

    // send msg continuously
    else if(!shell.substr(0,4).compare("send"))
    {
        string msg;      
        getline(cin, msg); // get data to send

        if(msg.size() <1)
        {
            // if don't enter msg, finish send function and return to shell
            prompt.clear();
            push_list(" # ");
            cout << endl;
        }
        else
        {
            // send msg to receiver
            msg_client = new MsgClient(this->receiver, msg);
            msg_client->Start();
            delete msg_client;
        }
    }
    else
    {
        prompt.clear();
        push_list(" # ");
        cout << endl;
    }
    return 0;
}

int Shell::cat(const string gitId)
{
    string fileName = gitId;
    size_t tokenlen = 0;

    // directory traversal mitigation
    while( fileName.find("/") != string::npos )
    {
         tokenlen = fileName.find("/");
         fileName = fileName.substr(tokenlen+1);
    }

    string filePath = "./MSG/" + fileName;
    ifstream openFile(filePath.data());

    // file open and read
    if(openFile.is_open())
    {
        string line;
        while(getline(openFile, line))
        {
            cout << line <<endl;
        }
        openFile.close();
        cout << endl;
    }
    else
    {
        cout << "[Error!] No file for " << filePath << endl;
    }

    return 0;
}

int Shell::ls()
{
    system("ls -l /home/jff/MSG/ | awk {'print $9'}");
    return 0;
}

int Shell::send(const string gitId)
{
    prompt.push_back("send @ <"+gitId+"> : ");
    return 0;
}

void Shell::push_list(const string v1)
{
    if(!v1.empty())
        prompt.push_back(v1);
}

void Shell::pop_list()
{
    if(!prompt.empty())
        prompt.pop_back();
}

void Shell::printMember()
{
    cout << " ::::::::::   ONLINE MEMBER LIST   :::::::::::" << endl;
    cout << " [*] Git Id (IP :: PGP Key Id)" << endl;
    for(std::pair<std::string, UserInfo*> element : UserInfoMap )
    {
        cout << " [+] " << element.first << " (";
        cout << element.second->GetIpAddr() << "::";
        cout << element.second->GetPGPKeyId() << ")" << endl;
    }
}

void Shell::printMyInfo()
{
    cout << " [*] " << myInfo->GetGithubId() << " (";
    cout << myInfo->GetIpAddr() << "::";
    cout << myInfo->GetPGPKeyId() << ")" << endl;
}

// To get passwd
int Shell::GetCh() {
    int ch;
    struct termios t_old, t_new;

    tcgetattr(STDIN_FILENO, &t_old);
    t_new = t_old;
    t_new.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t_new);

    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &t_old);
    return ch;
}

string Shell::GetPassword()
{
    const char BACKSPACE = 127;
    const char RETURN = 10;
    string password;
    unsigned char ch = 0;

    while((ch=GetCh()) != RETURN)
    {
        // when enter backspace, erase *
        if(ch == BACKSPACE)
        {
            if(password.length() != 0)
            {
                 cout << "\b \b";
                 password.resize(password.length()-1);
            }
        }
        // when enter keyboard, show * for privacy
        else
        {
            password += ch;
            cout <<'*';
        }
    }
    cout << endl;
    return password;
}

string Shell::GetPass()
{
    return private_pw;
}
