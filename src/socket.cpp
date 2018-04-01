#include "socket.h"

Socket::Socket() {}

Socket::~Socket() {}

bool Socket::Valid()
{
    if(this->sd < 0)
    {
        cout << "[Error!] Fail to create socket" << endl;
        return false;
    }
    return true;
}

int Socket::SetSockOpt(int level, int optname, const void *optval, socklen_t optlen)
{
	int rv = setsockopt(this->sd, level, optname, optval, optlen);
    if (rv == -1)
        cout << "[Error!] Fail to setsockopt" << endl;
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
        cout << "[Error!] Fail to bind" << endl;
    return rv;
}

int Socket::Connect(string ip_addr, int port)
{
    struct sockaddr_in serv_addr;
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip_addr.c_str(), &serv_addr.sin_addr) <= 0)
    {
        cout << "[Error!] Fail to inet_pton" << endl;
        return -1;
    }

    memset(serv_addr.sin_zero, '\0', sizeof serv_addr.sin_zero);

    int rv = connect(this->sd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (rv < 0)
        cout << "[Error!] Fail to connect" << endl;
    return rv;
}

UDPSocket::UDPSocket()
{
    int sd = socket(PF_INET, SOCK_DGRAM, 0);
    if (sd < 0)
        cout << "[Error!] Fail to create socket" << endl;
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

    if (len > MAX_UDP_BUF_SIZE)
        len = MAX_UDP_BUF_SIZE;

    int rv = sendto(this->sd, c_data, len, 0, (struct sockaddr*)&(this->recvaddr), sizeof recvaddr);
    if (rv < 0)
        cout << "[Error!] Fail to send data" << endl;
#ifdef SOCKER_LOG
    cout << data << endl;
#endif
    return rv;
}

string* UDPSocket::Recv()
{
    string *data = new string[2];
    char buf[MAX_UDP_BUF_SIZE];
    struct sockaddr_in src_addr;
    int addrlen = sizeof(src_addr);
    int rv = recvfrom(this->sd, buf, MAX_UDP_BUF_SIZE-1, 0, (struct sockaddr*)&src_addr, (socklen_t*)&addrlen);
    if (rv < 0)
    {
        cout << "[Error!] Fail to recv data" << endl;
        return data;
    }
#ifdef SOCKER_LOG
    cout << buf << endl;
#endif
    data[0] = buf;
    data[1] = inet_ntoa(src_addr.sin_addr);
    return data;
}

TCPSocket::TCPSocket()
{
    int sd = socket(PF_INET, SOCK_STREAM, 0);
    if (sd < 0)
        cout << "[Error!] Fail to create socket" << endl;
    this->sd = sd;
}

TCPSocket::TCPSocket(int sd)
{
    if (sd < 0)
        cout << "[Error!] Invalid socket descriptor" << endl;
    this->sd = sd;
}

TCPSocket* TCPSocket::Accept()
{
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    int client_sd = accept(this->sd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
    if (client_sd < 0)
        cout << "[Error!] Faile to accept" << endl;
    return new TCPSocket(client_sd);
}

TCPSocket::~TCPSocket()
{
	close(this->sd);
}

int TCPSocket::Send(string data)
{
    const char *c_data = data.c_str();
    int len = data.length();

#ifdef SOCKER_LOG
    cout << data << endl;
#endif
    int rv = send(this->sd, c_data, len, 0);
    if (rv < 0)
        cout << "[Error!] Fail to send data" << endl;
    return rv;
}

int TCPSocket::Listen(int backlog)
{
    int rv = listen(this->sd, backlog);
    if (rv < 0)
        cout << "[Error!] Fail to listen" << endl;
    return rv;
}

int TCPSocket::Recv(std::string& msg)
{
    int size_total = 0;
    char buffer[BUFF_SIZE];

    int size_read = recv(this->sd, buffer, BUFF_SIZE, 0);

    if (size_read <= 0)
    {
        return size_read;
    }
    msg.append(std::string(buffer, 0, size_read));
    size_total += size_read;

    // set non-blocking.
    SetNonblocking();

    while (size_read > 0)
    {
        memset(buffer, 0, BUFF_SIZE);
        size_read = recv(this->sd, buffer, BUFF_SIZE, 0);

        if (size_read < 0)
        {
            break;
        }

        msg.append(std::string(buffer, 0, size_read));
        size_total += size_read;
    }

    // set back to blocking
    SetBlocking();
    return size_total;
}

void TCPSocket::SetBlocking()
{
    int opts = fcntl(this->sd, F_GETFL);
    opts = opts & (~O_NONBLOCK);
    fcntl(this->sd, F_SETFL, opts);
}

void TCPSocket::SetNonblocking()
{
    fcntl(this->sd, F_SETFL, O_NONBLOCK);
}


