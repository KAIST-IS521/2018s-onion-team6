#include "socketaddress.h"

SocketAddress::SocketAddress()
{

}
SocketAddress::SocketAddress(struct sockaddr_in addr)
{
    this->port = addr.sin_port;

    char ip[INET_ADDRSTRLEN];
    inet_ntop(addr.sin_family, &(addr.sin_addr), ip, INET_ADDRSTRLEN);

    this->address = std::string(ip);
}
SocketAddress::SocketAddress(std::string address, int port)
{
    this->address = address;
    this->port = port;
}
struct sockaddr_in SocketAddress::get_struct()
{
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof addr);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(this->port);

    inet_aton(this->address.c_str(), &addr.sin_addr);

    return addr;
}
int SocketAddress::get_port()
{
    return this->port;
}
std::string SocketAddress::get_address()
{
    return this->address;
}
