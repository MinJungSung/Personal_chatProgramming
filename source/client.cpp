#include "client.h"

#define BUFSIZE 1024

using namespace std;
void Client::send_recv(int i, int sockfd)
{
	char send_buf[BUFSIZE];
	char recv_buf[BUFSIZE];
	int nbyte_recvd;
	if (i == 0){
		fgets(send_buf, BUFSIZE, stdin);
		if (strcmp(send_buf , "quit\n") == 0) {
			exit(0);
		} else
			send(sockfd, send_buf, strlen(send_buf), 0);
	} else {
		nbyte_recvd = recv(sockfd, recv_buf, BUFSIZE, 0);
		recv_buf[nbyte_recvd] = '\0';
		printf("%s" , recv_buf);
		fflush(stdout);
	}
}
			
	
void Client::connect_request(int *sockfd, struct sockaddr_in *server_addr)
{
	if ((*sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("Socket");
		exit(1);
	}
	server_addr->sin_family = AF_INET;
	server_addr->sin_port = htons(4950);
	server_addr->sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(server_addr->sin_zero, '\0', sizeof server_addr->sin_zero);

	if(connect(*sockfd, (struct sockaddr *)server_addr, sizeof(struct sockaddr)) == -1) {
		perror("connect");
		exit(1);
	}

	cout << "Do you wnat to (1)create an account, (2)login, or (3)exit?";
	cin >> option;

	cout << "ID: "; 
	cin >> id;
	cout << "Password: ";
	cin >> password;

	// For each Client, we need one clientInfo
	clientInfo.setId(id);
	clientInfo.setPassword(password);
	clientInfo.setRoomNo(0);


	//Server server;
	insertClientInfo(clientInfo);
}

// int Client::getOption() {
// 	return option;
// }

// ClientInfo Client::getClientInfo() {
// 	return clientInfo;
// }

std::string Client::toString() 
{
	return std::to_string(sockfd);
}

void Client::tcpListener(int sockfd, int fdmax, int i, struct sockaddr_in server_addr, fd_set master, fd_set read_fds) 
{
	connect_request(&sockfd, &server_addr);
	FD_ZERO(&master);
	FD_ZERO(&read_fds);
	FD_SET(0, &master);
	FD_SET(sockfd, &master);
	fdmax = sockfd;

	while(1){
		read_fds = master;
		if(select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1){
			perror("select");
			exit(4);
		}
		
		for(i=0; i <= fdmax; i++ )
			if(FD_ISSET(i, &read_fds))
				send_recv(i, sockfd);
	
	}
	printf("client-quited\n");
	close(sockfd);
}

int main()
{
	int sockfd, fdmax, i;
	struct sockaddr_in server_addr;
	fd_set master;
	fd_set read_fds;;

	Client client;
	client.tcpListener(sockfd, fdmax, i, server_addr, master, read_fds);
	return 0;
}
