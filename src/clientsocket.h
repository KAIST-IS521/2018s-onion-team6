#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string>
#include <unistd.h>
#include <cerrno>
#include <string>
#include <fcntl.h>

#include "socketaddress.h"

class clientsocket
{
    protected:
        int sock_fd;
        struct sockaddr_in address;
        socketaddress* sockaddr;

    public:
        clientsocket();
        clientsocket(int socket, struct sockaddr_in addr);
        ~clientsocket();

		int send(std::string);
		int send(const char*, int, int);
		int read(std::string&);
		int read(char*, int);
		void set_blocking();
		void set_nonblocking();
		void close()
		{
			if (sock_fd == -1)
			{
				return;
			}
			::close(sock_fd);
		}
		bool valid()
		{
			return sock_fd != -1;
		}
		int get_socket()
		{
			return sock_fd;
		}
		socketaddress* get_sockaddr()
		{
			return sockaddr;
		}
};
#endif
