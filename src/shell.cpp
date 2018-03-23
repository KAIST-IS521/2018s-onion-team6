#include "shell.h"
#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

extern UserInfo * myInfo;

Shell::Shell()
{
    login();
}
void Shell::run()
{
    push_list("#");
    while(1) cshell();

}
void Shell::login()
{
    string s_id;
    string s_pw;


    cout << "GIT_ID > ";
    cin >>s_id;
    cout << "PASS > ";
    cin >>s_pw;
    private_id = s_id;
    private_pw = s_pw;
    myInfo->SetGithubId(s_id);

}
string Shell::GetPass()
{
    return private_pw;
}
void Shell::usage()
{
    cout << "USAGE :#[COMMAND]" << endl;
    cout << "         {help}                        : print usage"<< endl;
    cout << "         {send} {GIT_ID}               : send message" << endl;
    cout << "                          -> {MESSAGE} : input message" <<endl;
    cout << "         {ls}                          : show received message list " << endl;
    cout << "         {cat} {GIT_ID}                : print recvived message" << endl;
    cout << "         {exit}                        : program exit" << endl;
    cout << endl;
}

int Shell::printPrompt()
{
    if(!prompt.empty())
    {
        list <string>::iterator itor;
        for(itor = prompt.begin(); itor!= prompt.end();itor++)
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

int Shell::cshell()
{
    printPrompt();
    list<string>::iterator iter = prompt.end();
    string shell=(*--iter);
/*
    cout << "--------------" <<endl;
    cout << shell  << endl;
    cout << "--------------" <<endl;
*/
    setbuf(stdin,NULL);
    setbuf(stdout,NULL);
    if(!shell.substr(0,1).compare("#"))
    {
        string cmd;
        getline(cin,cmd);

        if( !cmd.substr(0,4).compare("help") || !cmd.substr(0,1).compare("?") )
        {
            usage();
        }
        else if( !cmd.substr(0,2).compare("ls") )
        {
            ls();
        }
        else if ( !cmd.substr(0,3).compare("cat"))
        {
            if(cmd.size()>4)
                cat(cmd.substr(4,250)); //max path size is 255
        }
        else if ( !cmd.substr(0,4).compare("exit") )
        {
            exit(0);
        }
        else if ( !cmd.substr(0,4).compare("send") )
        {
            if(cmd.size()>5)
                send(cmd.substr(5,250));
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
            push_list("#");
        }
    }
    else
    {
        prompt.clear();
        push_list("#");
    }

    return 1;
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
    // [!] Verify gitId list
    //if( SERCH LIST( gitId )) {}
    prompt.push_back("send @ <"+gitId+"> : ");

    // SEND SOCKET MESAGE

    return 0;
}
