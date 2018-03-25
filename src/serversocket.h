#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cerrno>
#include "clientsocket.h"

class serversocket
{
	protected:
		int port;
		int backlog;
		int sock_fd;
		std::string address;

	public:
       //         serversocket();
		serversocket(int port)
		{
			this->port = port;
			backlog = 10;
			address = "0.0.0.0";
		}

                /*
                serversocket(int port, int backlog)
		{
			this->port = port;
			this->backlog = backlog;
			address = "0.0.0.0";
		}
		serversocket(int port, int backlog, std::string address)
		{
			this->port = port;
			this->backlog = backlog;
			this->address = address;
		}
*/
		~serversocket();

		int listen();
		clientsocket* accept();
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
};


#endif
