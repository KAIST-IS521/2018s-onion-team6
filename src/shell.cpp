#include "shell.h"
#include <iostream>
#include <cstdlib>
#include <fstream>

Shell::Shell()
{
    Login();
    pgpmanager = new PgpManager(this->private_pw);
}

void Shell::Run()
{
    push_list(" # ");
    usage();
    while(1) CShell();
}

void Shell::Login()
{
    string s_id;
    string s_pw;

    cout << this->banner << endl;

    cout << "[+] GIT_ID > ";
    cin >> s_id;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    cout << "[+] Private key password > ";
    s_pw = GetPassword();

    private_id = s_id;
    private_pw = s_pw;
    myInfo->SetGithubId(s_id);
}

void Shell::usage()
{
    cout << "USAGE :# [COMMAND]" << endl;
    cout << "         {help}                        : print usage" << endl;
    cout << "         {send} {GIT_ID}               : send message" << endl;
    cout << "                          -> {MESSAGE} : input message" << endl;
    cout << "         {ls}                          : show received message list " << endl;
    cout << "         {cat} {GIT_ID}                : print recvived message" << endl;
    cout << "         {w}                           : show member list" << endl;
    cout << "         {exit}                        : program exit" << endl;
    cout << endl;
}

int Shell::PrintPrompt()
{
    if(!prompt.empty())
    {
        list <string>::iterator itor;
        for(itor=prompt.begin(); itor!=prompt.end(); itor++)
            cout << *itor;
    }
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
    cout << "::::::::::   ONLINE MEMBER LIST   :::::::::::" << endl;
    for(std::pair<std::string, UserInfo*> element : UserInfoMap )
        cout << "[+] " << element.first << endl;
}

int Shell::CShell()
{
    PrintPrompt();
    ParseCmd();
    return 1;
}

int Shell::ParseCmd()
{
    list<string>::iterator iter = prompt.end();
    string shell=(*--iter);

    setbuf(stdin, NULL);
    setbuf(stdout, NULL);

    if(!shell.substr(0,3).compare(" # "))
    {
        string cmd;
        getline(cin, cmd);

        if(!cmd.substr(0,4).compare("help") || !cmd.substr(0,1).compare("?"))
        {
            usage();
        }
        else if(!cmd.substr(0,2).compare("ls"))
        {
            ls();
        }
        else if (!cmd.substr(0,3).compare("cat"))
        {
            if(cmd.size() > 4)
                cat(cmd.substr(4,250)); //max path size is 255
        }
        else if (!cmd.substr(0,4).compare("exit"))
        {
            exit(0);
        }
        else if (!cmd.substr(0,1).compare("w"))
        {
            printMember();
        }
        else if (!cmd.substr(0,4).compare("send"))
        {
            if(cmd.size()>5)
            {
                this->receiver = cmd.substr(5,250);
                send(this->receiver);
            }
        }
        else
        {
            usage();
        }
    }
    else if(!shell.substr(0,4).compare("send"))
    {
        string msg;
        getline(cin,msg); // cmd will be message
        //SEARCH GIT_ID LIST IN MEMBER CLASS
        if(msg.size() <1)
        {
            prompt.clear();
            push_list(" # ");
            cout << endl;
            delete msg_client;
        }
        else
        {
            msg_client = new MsgClient(this->receiver, msg);
            msg_client->Start();
        }
    }
    else
    {
        prompt.clear();
        push_list(" # ");
        cout <<endl;
    }
    return 0;
}

int Shell::cat(const string gitId)
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
    ifstream openFile(fileName.data());
    if(openFile.is_open())
    {
        string cmd;
        string line;
        while(getline(openFile, line))
        {
            cout<< line <<endl;
        }
        cout << endl;
    }
    else
    {
        cout << "No file for " << gitId << endl;
    }

    return 0;
}

int Shell::ls()
{
    cout << "[D] shell::ls() "<< endl;
    return 0;
}

int Shell::send(const string gitId)
{
    prompt.push_back("send @ <"+gitId+"> : ");
    return 0;
}

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
        if(ch == BACKSPACE)
        {
            if(password.length() != 0)
            {
                 cout << "\b \b";
                 password.resize(password.length()-1);
            }
        }
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
