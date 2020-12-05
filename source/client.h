#ifndef CLIENT_H
#define CLIENT_H
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <cstdint>
#include <iostream>
#include <cstring>
#include "clientInfo.h"
#include "server.h"

#define BUFSIZE 1024

using namespace std;

class Client {

public:

	// Create a connection and send messages
	void send_recv(int i, int sockfd);
	void connect_request(int* sockfd, struct sockaddr_in *server_addr);
	// TODO: why is option returning wrong result?
	int getOption(){
	cout << option << endl;
	return option;};
	ClientInfo getClientInfo(){return clientInfo;};
	
	void tcpListener(int sockfd, int fdmax, int i, struct sockaddr_in server_addr, fd_set master, fd_set read_fds);

	// Print sockfd to string
	std::string toString();

private:

	int sockfd, fdmax, i;
	struct sockaddr_in server_addr;
	fd_set master;
	fd_set read_fds;

	std::string id, password; 
	int option;
	ClientInfo clientInfo;
		
	//CreateLogin createLogin;
};
#endif
