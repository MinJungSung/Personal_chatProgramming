#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <cstdint>

#define BUFSIZE 1024

class Client {

public:

	Client();
	~Client();

	void send_recv(int i, int sockfd);
	void connect_request(int* sockfd, struct sockaddr_in *server_addr);
	void tcpListener(int sockfd, int fdmax, int i, struct sockaddr_in server_addr, fd_set master, fd_set read_fds);
	std::string toString();

private:

	int sockfd, fdmax, i;
	struct sockaddr_in server_addr;
	fd_set master;
	fd_set read_fds;


};
