#include "server.h"
void Server::send_recv(int i, fd_set *master, int sockfd, int fdmax)
{
	int nbytes_recvd;
	char recv_buf[BUFSIZE];

	if ((nbytes_recvd = recv(i, recv_buf, sizeof(recv_buf) - 1, 0)) <= 0) {
		if (nbytes_recvd == 0) {
			requestHandler.requestDispatcher(i, "disconnected");
			printf("socket %d hung up\n", i);
		}else {
			perror("recv");
		}
		close(i);
		FD_CLR(i, master);
	} else if(nbytes_recvd > 1){ 	
		string recv_buf_toString(recv_buf);
		trim(recv_buf_toString);
		printf("Server side received message: %s \n", recv_buf);
		//printf("Size of recv_buf %s \n", sizeof(recv_buf));
		//printf("Strlen of recv_buf %s \n", strlen(recv_buf));
		cout << sizeof(recv_buf) << endl;
		cout << strlen(recv_buf) << endl;
		requestHandler.requestDispatcher(i, recv_buf_toString);
	}	
}

void Server::connection_accept(fd_set *master, int *fdmax, int sockfd, struct sockaddr_in *client_addr)
{
	socklen_t addrlen;
	int newsockfd;
	
	addrlen = sizeof(struct sockaddr_in);
	if((newsockfd = accept(sockfd, (struct sockaddr *)client_addr, &addrlen)) == -1) {
		perror("accept");
		exit(1);
	}else {
		FD_SET(newsockfd, master);
		requestHandler.setDefault(newsockfd, master);
		if(newsockfd > *fdmax){
			*fdmax = newsockfd;
		}
		requestHandler.requestDispatcher(sockfd, "connected");
		printf("new connection from %s on port %d \n",inet_ntoa(client_addr->sin_addr), ntohs(client_addr->sin_port));
	}
}
	
void Server::connect_request(int *sockfd, struct sockaddr_in *my_addr)
{
	int yes = 1;
		
	if ((*sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("Socket");
		exit(1);
	}
		
	my_addr->sin_family = AF_INET;
	my_addr->sin_port = htons(4950);
	my_addr->sin_addr.s_addr = INADDR_ANY;
	memset(my_addr->sin_zero, '\0', sizeof my_addr->sin_zero);
		
	if (setsockopt(*sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
		perror("setsockopt");
		exit(1);
	}
		
	if (bind(*sockfd, (struct sockaddr *)my_addr, sizeof(struct sockaddr)) == -1) {
		perror("Unable to bind");
		exit(1);
	}
	if (listen(*sockfd, 10) == -1) {
		perror("listen");
		exit(1);
	}
	printf("\nTCPServer Waiting for client on port 4950\n");
	fflush(stdout);
}

void Server::tcpListener(int sockfd, int fdmax, struct sockaddr_in my_addr, struct sockaddr_in client_addr, fd_set master, fd_set read_fds)
{
	
	FD_ZERO(&master);
	FD_ZERO(&read_fds);
	connect_request(&sockfd, &my_addr);
	FD_SET(sockfd, &master);
	fdmax = sockfd;
	
	while(1){
		read_fds = master;
		if(select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1){
			perror("select");
			exit(4);
		}
		for (int i = 0; i <= fdmax; i++){
			if (FD_ISSET(i, &read_fds)){
				if (i == sockfd){
					connection_accept(&master, &fdmax, sockfd, &client_addr);
				} else{
					send_recv(i, &master, sockfd, fdmax);
				}
			}
		}
	}
}


int main()
{
	
	fd_set master;
	fd_set read_fds;
	int fdmax, i;
	int sockfd = 0;
	struct sockaddr_in my_addr, client_addr;

	Server server;
	server.tcpListener(sockfd, fdmax, my_addr, client_addr, master, read_fds);
	return 0;
}

