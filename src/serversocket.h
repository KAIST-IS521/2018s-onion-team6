#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

<<<<<<< HEAD
=======
#include<iostream>
>>>>>>> bbeb5875831d01fb0e3ab16dd0439d37f64f5a4d
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cerrno>
<<<<<<< HEAD
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
=======

#include "clientsocket.h"

using namespace std;

class ServerSocket
{ 
protected:
    int port;
    int backlog;
    int sock_fd;
    std::string address;

public:
    ServerSocket();
    ServerSocket(int port);
    ServerSocket(int port, int backlog);
    ServerSocket(int port, int backlog, std::string address);
    ~ServerSocket();

    int listen();
    ClientSocket* accept();
    void close();
    bool valid();
    int get_socket();
};

#endif // SERVERSOCKET_H
>>>>>>> bbeb5875831d01fb0e3ab16dd0439d37f64f5a4d
