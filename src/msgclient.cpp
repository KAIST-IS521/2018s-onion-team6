#include "msgclient.h"

MsgClient::MsgClient(string receiver, string msg)
{
    this->receiver = receiver;
    this->msg = msg;
}

void MsgClient::Start()
{
    if (CheckReceiver())
    {
        SetRoute();
        SendMessage();
    }
}

bool MsgClient::CheckReceiver()
{
    if(UserInfoMap.find(this->receiver) == UserInfoMap.end())
        return false;
    return true;
}
int MsgClient::SetRoute()
{
    int i = 0;
    int maxsize = UserInfoMap.size();
    if(maxsize > 2 && maxsize < 100 )
    {
        for(i = 0; i < maxsize; i++)
        {
            node_list[i]="";
        }
        i=0;

        for (std::pair<std::string, UserInfo * > element : UserInfoMap )
        {
            node_list[i]=element.first;
            i++;
        }
        int j = 0;
        string tmp;
        srand(time(NULL));
        for(i = maxsize-1 ; i > 0; i--)
        {
            j = rand() % i;
            std::swap(node_list[i],node_list[j]);
        }

        //for(i = 0; i < maxsize; i++)
        //    cout << "[D]"<<node_list[i] <<endl;
    }
    else
    {
        cout << "NODE ARE NOT EHOUGH" <<endl;
        exit(0);
    }
    return 0;
}

int MsgClient::SendMessage()
{
return 0;
}
