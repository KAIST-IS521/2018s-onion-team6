#include "user_info.h"

UserInfo::UserInfo(){}

UserInfo::~UserInfo(){}

// Getter and Setter for UserInfo fields
string UserInfo::GetGithubId()
{
    return this->github_id;
}

void UserInfo::SetGithubId(string github_id)
{
    this->github_id = github_id;
}

string UserInfo::GetIpAddr()
{
    return this->ip_addr;
}

void UserInfo::SetIpAddr(string ip_addr)
{
    this->ip_addr = ip_addr;
}

string UserInfo::GetPGPKeyId()
{
    return this->pgp_key_id;
}

void UserInfo::SetPGPKeyId(string pgp_key_id)
{
    this->pgp_key_id = pgp_key_id;
}
