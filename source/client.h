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
#include <client.cpp>

#define BUFSIZE 1024

class Client {

public:

	Client();
	~Client();

	int sockfd, fdmax, i;
	struct sockaddr_in server_addr;
	fd_set master;
	fd_set read_fds;
	
	connect_request(&sockfd, &server_addr);
	FD_ZERO(&master);
	FD_ZERO(&read_fds);
	FD_SET(0, &master);
	FD_SET(sockfd, &master);
	fdmax = socksfd;

	void send_recv(int i, int sockfd){};
	void connect_request(int* sockfd, struct sockaddr_in *server_addr){};
	void tcpListener(){};	

private:


}
