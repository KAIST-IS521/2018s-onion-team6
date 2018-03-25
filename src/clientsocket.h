<<<<<<< HEAD
#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H
=======
#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H
>>>>>>> bbeb5875831d01fb0e3ab16dd0439d37f64f5a4d

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
<<<<<<< HEAD
#include <string>
#include <unistd.h>
#include <cerrno>
#include <string>
#include <fcntl.h>

#include "socketaddress.h"

class clientsocket
=======
#include <cstring>
#include <unistd.h>
#include <cerrno>
#include <fcntl.h>

#include "config.h"
#include "socketaddress.h"

using namespace std;

class ClientSocket
>>>>>>> bbeb5875831d01fb0e3ab16dd0439d37f64f5a4d
{
    protected:
        int sock_fd;
        struct sockaddr_in address;
<<<<<<< HEAD
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
=======
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
>>>>>>> bbeb5875831d01fb0e3ab16dd0439d37f64f5a4d
