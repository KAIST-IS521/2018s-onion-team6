#include "clientsocket.h"

<<<<<<< HEAD
#define BUFF_SIZE 128

clientsocket::clientsocket()
{
}

clientsocket::clientsocket(int socket, struct sockaddr_in addr)
{
    sock_fd = socket;
    address = addr;
    sockaddr = new socketaddress(addr);
}

clientsocket::~clientsocket()
{
	delete sockaddr;
	close();
}
int clientsocket::send(std::string data)
{
	return send(data.c_str(), data.length(), 0);
}
int clientsocket::send(const char* buf, int len, int flags)
{
	return ::send(sock_fd, buf, len, flags);
}
int clientsocket::read(char* buf, int len)
{
	return ::recv(sock_fd, buf, len, 0);
}
int clientsocket::read(std::string& msg)
{
	int size_total = 0;
	char buffer[BUFF_SIZE];

	int size_read = recv(sock_fd, buffer, BUFF_SIZE, 0);

	if (size_read <= 0)
	{
		return size_read;
	}

	msg.append(std::string(buffer, 0, size_read));
	size_total += size_read;

	// set non-blocking.
	set_nonblocking();

	while (size_read > 0)
	{
		memset(buffer, 0, BUFF_SIZE);
		size_read = recv(sock_fd, buffer, BUFF_SIZE, 0);

		if (size_read < 0)
		{
			break;
		}

		msg.append(std::string(buffer, 0, size_read));
		size_total += size_read;
	}

	// set back to blocking
	set_blocking();

	return size_total;
}
void clientsocket::set_blocking()
{
	int opts = fcntl(sock_fd, F_GETFL);
	opts = opts & (~O_NONBLOCK);
	fcntl(sock_fd, F_SETFL, opts);
}
void clientsocket::set_nonblocking()
{
	fcntl(sock_fd, F_SETFL, O_NONBLOCK);
}

=======
ClientSocket::ClientSocket()
{
}

ClientSocket::ClientSocket(int socket, struct sockaddr_in addr)
{
    this->sock_fd = socket;
    this->address = addr;
    this->sockaddr = new SocketAddress(addr);
}
ClientSocket::~ClientSocket()
{
    delete this->sockaddr;
    close();
}

int ClientSocket::send(std::string data)
{
    return this->send(data.c_str(), data.length(), 0);
}
int ClientSocket::send(const char* buf, int len, int flags)
{
    return ::send(this->sock_fd, buf, len, flags);
}
int ClientSocket::read(char* buf, int len)
{
    return ::recv(this->sock_fd, buf, len, 0);
}
int ClientSocket::read(std::string& msg)
{
    int size_total = 0;
    char buffer[BUFF_SIZE];

    int size_read = recv(this->sock_fd, buffer, BUFF_SIZE, 0);

    if (size_read <= 0)
    {
        return size_read;
    }

    msg.append(std::string(buffer, 0, size_read));
    size_total += size_read;

    // set non-blocking.
    set_nonblocking();

    while (size_read > 0)
    {
        memset(buffer, 0, BUFF_SIZE);
        size_read = recv(this->sock_fd, buffer, BUFF_SIZE, 0);

        if (size_read < 0)
        {
            break;
        }

        msg.append(std::string(buffer, 0, size_read));
        size_total += size_read;
    }

    // set back to blocking
    set_blocking();

    return size_total;

}
void ClientSocket::set_blocking()
{
    int opts = fcntl(this->sock_fd, F_GETFL);
    opts = opts & (~O_NONBLOCK);
    fcntl(this->sock_fd, F_SETFL, opts);
}
void ClientSocket::set_nonblocking()
{
    fcntl(this->sock_fd, F_SETFL, O_NONBLOCK);
}

void ClientSocket::close()
{
    if (this->sock_fd == -1)
    {
        return;
    }
    ::close(this->sock_fd);
}
bool ClientSocket::valid()
{
    return sock_fd != -1;
}
int ClientSocket::get_socket()
{
    return this->sock_fd;
}
SocketAddress* ClientSocket::get_sockaddr()
{
    return this->sockaddr;
}
>>>>>>> bbeb5875831d01fb0e3ab16dd0439d37f64f5a4d
