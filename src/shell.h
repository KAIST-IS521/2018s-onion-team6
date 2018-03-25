#ifndef SHELL_H
#define SHELL_H

#include<iostream>
#include<list>

#include "user_info.h"

using namespace std;

extern UserInfo* myInfo;

class Shell
{
    private:
        string private_id;
        string private_pw;
        list <string> prompt;

    public:
        Shell();
        ~Shell();
        void run();
        void login();
        string GetPass();
        int printPrompt();
        void push_list(const string v1);
        void pop_list();
        int cshell();
        void usage();
        int cat(const string v1);
        int ls();
        int send(const string v1);

};

#endif // SHELL_H
