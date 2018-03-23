#ifndef SOCKET_H
#define SOCKET_H

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string>
#include <unistd.h>
#include <cerrno>

#include "socketaddress.h"


class tcpsocket
{
	protected:
		int sock_fd;
		struct sockaddr_in address;
		socketaddress* sockaddr;

	public:
		tcpsocket() {}
		tcpsocket(int socket, struct sockaddr_in addr)
		{
			sock_fd = socket;
			address = addr;
			sockaddr = new socketaddress(addr);
		}
		~tcpsocket();

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