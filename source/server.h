#ifndef SERVER_H
#define SERVER_H

#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <map>
#include <list>

#include <fstream>
#include <string>
#include "requestHandler.h"

#include "function_pool.h"
#include <mutex>
#include <thread>
#include <vector>

#define PORT 4950
#define BUFSIZE 1024
#define MAX_SOCK 1024

using namespace std;

class Server {
public:

	void send_recv(int i, fd_set* master, int sockfd, int fmax);
	void connection_accept(fd_set* master, int* fdmax, int sockfd, struct sockaddr_in* client_addr);
	void connect_request(int* sockfd, struct sockaddr_in* my_addr);
	void tcpListener(int sockfd, int fdmax, struct sockaddr_in my_addr, struct sockaddr_in client_addr, fd_set master, fd_set read_fds);

	RequestHandler requestHandler;
	Function_pool func_pool;
	
	int num_threads = thread::hardware_concurrency();
	vector<thread> thread_pool;
	for(int thread_count = 0; thread_count < num_threads; thread_count++){
		thread_pool.push_back(thread(&Function_pool::infinite_loop_func, &func_pool));
	}
};
#endif
