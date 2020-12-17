#ifndef SERVER_H
#define SERVER_H

#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <map>
#include <list>
///////////////////////////////
#include <fstream>
#include <string>
#include "clientInfo.h"

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/string.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/algorithm/string.hpp>
//////////////////////////////

#define PORT 4950
#define BUFSIZE 1024
#define MAX_SOCK 1024

using namespace std;
/////////////////////////////
using std::cout;
using std::endl;
using std::cin;
using std::string;

namespace bst = boost;
////////////////////////////

class Server {
public:

	void send_to_all(int j, int i, int sockfd, int nbyte_recvd, char* recv_buf, fd_set* master);
	void send_recv(int i, fd_set* master, int sockfd, int fmax);
	void temprecv(int i, fd_set* master, int sockfd, int fmax);
	void connection_accept(fd_set* master, int* fdmax, int sockfd, struct sockaddr_in* client_addr);
	void connect_request(int* sockfd, struct sockaddr_in* my_addr);
	void tcpListener(int sockfd, int fdmax, int i, struct sockaddr_in my_addr, struct sockaddr_in client_addr, fd_set master, fd_set read_fds);

	map<int, int> room_list = {{0,0}};
	map<int, ClientInfo> client_list;		//map<sockfd, ClientInfo>

	fd_set master;
	fd_set read_fds;
	
	/* VARIABLE INFORMATION
	i == sender
	j == iterator
	sockfd == openned socket
	fdmax == highest socket number
	*/
	int fdmax, i;
	int sockfd = 0;
	struct sockaddr_in my_addr, client_addr;	
};
#endif
