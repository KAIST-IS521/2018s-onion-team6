#ifndef USER_INFO_H
#define USER_INFO_H

#include<iostream>

using namespace std;

class UserInfo
{
    public:
        UserInfo();
        ~UserInfo();

        string GetGithubId();
        void SetGithubId(string github_id);

        string GetIpAddr();
        void SetIpAddr(string ip_Addr);

        string GetPGPKeyId();
        void SetPGPKeyId(string pgp_key_id);

    private:
        string github_id;
        string ip_addr;
        string pgp_key_id;
};

#endif // USER_INFO_H
