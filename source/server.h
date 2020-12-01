#ifndef SERVER
#define SERVER

#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <map>
#include "client.h"
#include "createLogin.h"
#include "room.h"

#define PORT 4950
#define BUFSIZE 1024
#define MAX_SOCK 1024

class Server {
public:

	void send_to_all(int j, int i, int sockfd, int nbyte_recvd, char* recv_buf, fd_set* master);
	void send_recv(int i, fd_set* master, int sockfd, int fmax);
	void connection_accept(fd_set* master, int* fdmax, int sockfd, struct sockaddr_in* client_addr);
	void connect_request(int* sockfd, struct sockaddr_in* my_addr);
	void tcpListener(int sockfd, int fdmax, int i, struct sockaddr_in my_addr, struct sockaddr_in client_addr, fd_set master, fd_set read_fds);
	void makeEnterRoom(int sockfd);
	void sent_to_room(int j, int i, int sockfd, int nbyte_recvd, char* recv_buf, fd_set* master);

private:

	// Create ClientInfo list
	// socketfd == portNo
	std::map<int, std::list<int>> roomClient;	//map<roomNo, portNo>
	std::map<int, ClientInfo> onlineClient;	//list<portNo, id an password>

	fd_set master;
	fd_set read_fds;
	
	// i == sender
	// j == iterator
	// sockfd == openned socket
	// fdmax == highest socket number
	int fdmax, i, room;
	int sockfd = 0;
	struct sockaddr_in my_addr, client_addr;	

};

#endif
