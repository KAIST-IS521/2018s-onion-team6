#ifndef SHELL_H
#define SHELL_H

#include<iostream>
#include<list>
#include<cstring>
#include <cstdio>
#include <termios.h>

#include "user_info.h"
#include "msgserver.h"
#include "msgclient.h"

using namespace std;

extern UserInfo* myInfo;
extern unordered_map<string, UserInfo*> UserInfoMap;

class Shell
{
    public:
        Shell();
        ~Shell();
        void Run();

    private:
        string private_id;
        string private_pw;
        list <string> prompt;
        string receiver;
        MsgClient *msg_client;

        void Login();
        int GetCh();
        string GetPassword();

        int CShell();
        int PrintPrompt();
        int ParseCmd();

        void push_list(const string v1);
        void pop_list();

        void usage();
        int cat(const string v1);
        int ls();
        int send(const string v1);
        void printMember();

        string GetPass();

        string banner = "\n\n::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n                     _ _____ _____    ___        _             \n                    | |  ___|  ___|  / _ \\ _ __ (_) ___  _ __  \n                 _  | | |_  | |_    | | | | '_ \\| |/ _ \\| '_ \\ \n                | |_| |  _| |  _|   | |_| | | | | | (_) | | | |\n                 \\___/|_|   |_|      \\___/|_| |_|_|\\___/|_| |_|\n                                                               \n                __  __                                           \n               |  \\/  | ___  ___ ___  __ _ _ __   __ _  ___ _ __ \n               | |\\/| |/ _ \\/ __/ __|/ _` | '_ \\ / _` |/ _ \\ '__|\n               | |  | |  __/\\__ \\__ \\ (_| | | | | (_| |  __/ |   \n               |_|  |_|\\___||___/___/\\__,_|_| |_|\\__, |\\___|_|   \n                                                 |___/           \n::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n";
};

#endif // SHELL_H
