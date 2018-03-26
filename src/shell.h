#ifndef SHELL_H
#define SHELL_H

#include<iostream>
#include<list>

#include "user_info.h"
#include "msgserver.h"
#include "msgclient.h"

using namespace std;

extern UserInfo* myInfo;

class Shell
{
    private:
        string private_id;
        string private_pw;
        list <string> prompt;
        string receiver;

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
        string banner = "\n\n::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n                     _ _____ _____    ___        _             \n                    | |  ___|  ___|  / _ \\ _ __ (_) ___  _ __  \n                 _  | | |_  | |_    | | | | '_ \\| |/ _ \\| '_ \\ \n                | |_| |  _| |  _|   | |_| | | | | | (_) | | | |\n                 \\___/|_|   |_|      \\___/|_| |_|_|\\___/|_| |_|\n                                                               \n                __  __                                           \n               |  \\/  | ___  ___ ___  __ _ _ __   __ _  ___ _ __ \n               | |\\/| |/ _ \\/ __/ __|/ _` | '_ \\ / _` |/ _ \\ '__|\n               | |  | |  __/\\__ \\__ \\ (_| | | | | (_| |  __/ |   \n               |_|  |_|\\___||___/___/\\__,_|_| |_|\\__, |\\___|_|   \n                                                 |___/           \n::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n";
};

#endif // SHELL_H
