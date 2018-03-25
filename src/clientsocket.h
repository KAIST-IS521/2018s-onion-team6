#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>
#include <cerrno>
#include <fcntl.h>

#include "config.h"
#include "socketaddress.h"

using namespace std;

class ClientSocket
{
    protected:
        int sock_fd;
        struct sockaddr_in address;
        SocketAddress* sockaddr;

    public:
        ClientSocket();
        ClientSocket(int socket, struct sockaddr_in addr);
        ~ClientSocket();

        int send(std::string data);
        int send(const char*, int, int);
        int read(std::string& msg);
        int read(char*, int);
        void set_blocking();
        void set_nonblocking();
        void close();
        bool valid();
        int get_socket();
        SocketAddress* get_sockaddr();

};

#endif // CLIENTSOCKET_H
