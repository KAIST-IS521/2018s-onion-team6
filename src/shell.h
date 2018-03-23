#ifndef SHELL_H
#define SHELL_H
#include<iostream>
#include<list>
using namespace std;

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
