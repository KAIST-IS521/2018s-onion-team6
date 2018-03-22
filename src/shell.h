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
        Shell(const string id, const string pw );
        ~Shell();
        int printPrompt();
        void push_list(const string v1);
        void pop_list();
};

#endif // SHELL_H
