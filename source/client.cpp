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
}

string Client::toString() 
{
	return to_string(sockfd);
}

void Client::tcpListener(int sockfd, int fdmax, int i, struct sockaddr_in server_addr, fd_set master, fd_set read_fds) 
{
	connect_request(&sockfd, &server_addr);
	FD_ZERO(&master);
	FD_ZERO(&read_fds);
	FD_SET(0, &master);
	FD_SET(sockfd, &master);
	fdmax = sockfd;
	send_clientInformation(sockfd);

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

///////////////////////////////////////////////////////////
string Client::setClientInformation()
{
	string clientInfo = "";
	string temp = "";
	cout << "Username: ";
	cin >> temp;
	clientInfo = clientInfo + temp;
	cout << "Password: ";
	cin >> temp;
	clientInfo = clientInfo + "," + temp + "0," + to_string(sockfd);
	return clientInfo;
}

void Client::send_clientInformation(int sockfd)
{
	string s = setClientInformation();
	char send_buf[BUFSIZE];
	strcpy(send_buf, s.c_str());

	if (i == 0){
		if (strcmp(send_buf , "quit\n") == 0) {
			exit(0);
		} else
			send(sockfd, send_buf, strlen(send_buf), 0);
	}
}
///////////////////////////////////////////////////////////
