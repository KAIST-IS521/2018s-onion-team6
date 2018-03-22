#include "shell.h"
#include <iostream>

using namespace std;
Shell::Shell(const string id, const string pw)
{
    // Create RecvSocke
    private_id = id;
    private_pw = pw;
    push_list(">");
    push_list(id);

    printPrompt();




}

int Shell::printPrompt()
{
//    if(!(list

    // waiting command
    // command parsing
    // help
    // sendmsg
    // sendmsg>[git_id]
    // ls
    // cat
    // ...
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

