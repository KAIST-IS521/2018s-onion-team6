#include "socket.h"

Socket::Socket()
{

}

Socket::~Socket()
{

}

int Socket::SetSockOpt(int level, int optname, const void *optval, socklen_t optlen)
{
	int rv = setsockopt(this->sd, level, optname, optval, optlen);
    if (rv == -1)
    {
        perror("setsockopt");
        exit(-1);
    }
    return rv;
}

int Socket::Bind(int port)
{
	struct sockaddr_in addr;
    memset(&addr, '0', sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);
    memset(addr.sin_zero, '\0', sizeof addr.sin_zero);

    int rv = bind(this->sd, (struct sockaddr *) &addr, sizeof addr);
    if (rv < 0)
    {
        perror("bind");
        exit(-1);
    }
    return rv;
}

int Socket::Connect(string ip_addr)
{
    struct sockaddr_in serv_addr;
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(MSG_SERVER_PORT);
    if(inet_pton(AF_INET, ip_addr.c_str(), &serv_addr.sin_addr)<=0)
    {
        perror("inet_pton");
        exit(-1);
    }
    //serv_addr.sin_addr.s_addr = inet_addr(ip_addr.c_str());
    memset(serv_addr.sin_zero, '\0', sizeof serv_addr.sin_zero);

    int rv = connect(this->sd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (rv < 0)
    {
        perror("connect");
        exit(-1);
    }
    return rv;
}

UDPSocket::UDPSocket()
{
    int sd = socket(PF_INET, SOCK_DGRAM, 0);
    if (sd < 0)
    {
        perror("socket");
        exit(-1);
    }
    this->sd = sd;
}

UDPSocket::~UDPSocket()
{
	close(this->sd);
}

void UDPSocket::SetDestAddr(const char* dest_addr, int port)
{
    memset(&(this->recvaddr), '0', sizeof(this->recvaddr));
    this->recvaddr.sin_family = AF_INET;
    this->recvaddr.sin_addr.s_addr = inet_addr(dest_addr);
    this->recvaddr.sin_port = htons(port);
    memset(this->recvaddr.sin_zero, '\0', sizeof this->recvaddr.sin_zero);
}

int UDPSocket::Send(string data)
{
    const char *c_data = data.c_str();
    int len = data.length();

    if(len > MAX_UDP_BUF_SIZE)
        len = MAX_UDP_BUF_SIZE;

    int rv = sendto(this->sd, c_data, len, 0, (struct sockaddr*)&(this->recvaddr), sizeof recvaddr);
    if (rv < 0)
    {
        perror("send");
        exit(-1);
    }
#ifdef SOCKER_LOG
    cout << data << endl;
#endif
    return rv;
}

string* UDPSocket::Recv()
{
    char buf[MAX_UDP_BUF_SIZE];
    struct sockaddr_in src_addr;
    int addrlen = sizeof(src_addr);
    int rv = recvfrom(this->sd, buf, MAX_UDP_BUF_SIZE-1, 0, (struct sockaddr*)&src_addr, (socklen_t*)&addrlen);
    if (rv < 0)
    {
        perror("recv");
        exit(-1);
    }
#ifdef SOCKER_LOG
    cout << buf << endl;
#endif
    string *data = new string[2];
    data[0] = buf;
    data[1] = inet_ntoa(src_addr.sin_addr);
    return data;
}

TCPSocket::TCPSocket()
{
    int sd = socket(PF_INET, SOCK_STREAM, 0);
    if (sd < 0)
    {
        perror("socket");
        exit(-1);
    }
    this->sd = sd;
}

TCPSocket::~TCPSocket()
{
	close(this->sd);
}
int TCPSocket::Send(string data)
{
    const char *c_data = data.c_str();
    int len = data.length();

    if(len > MAX_TCP_BUF_SIZE)
        len = MAX_TCP_BUF_SIZE;
#ifdef SOCKER_LOG
    cout << data << endl;
#endif
    int rv = send(this->sd, c_data, len, 0);
    if (rv < 0)
    {
        perror("send");
        exit(-1);
    }
    return rv;
}

int TCPSocket::Recv(size_t len)
{
	char buf[MAX_BUF_LEN];
    int rv = recv(this->sd, buf, len, 0);
#ifdef SOCKER_LOG
    cout << buf << endl;
#endif
    if (rv < 0)
    {
        perror("send");
        exit(-1);
    }
    return rv;
}


