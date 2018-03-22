#include "shell.h"
#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

Shell::Shell(const string id, const string pw)
{
    // Create RecvSocke
    private_id = id;
    private_pw = pw;
    push_list("#");

    while(1) cshell();

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
    string cmd;
    printPrompt();
    getline(cin,cmd);

    if( !cmd.compare("help") || !cmd.compare("?") )
        usage();
    else if( !cmd.compare("ls") )
        ls();
    else if ( !cmd.substr(0,3).compare("cat"))
        cat(cmd.substr(4,252)); //max size
    else if ( !cmd.compare("exit") )
        exit(0);
    else if ( cmd.substr(0,4).find("send") != string::npos )
    {
        string git_id;
        cout << "TARGET GIT_ID : ";
        cin >> git_id;
    }
    else
        usage();

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
        string line;
        while(getline(openFile, line))
        {
            cout<< line <<endl;
        }
        cout << endl;
    }
    return 0;
}
int Shell::ls()
{
    cout << "[D] shell::ls() "<<endl;
    // print recv message list
    //
    return 0;
}
int Shell::send()
{

    return 0;
}
