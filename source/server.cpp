#include "server.h"

using namespace std;

void Server::send_to_all(int j, int i, int sockfd, int nbytes_recvd, char *recv_buf, fd_set *master)
{
	if (FD_ISSET(j, master)){
		if (j != sockfd && j != i) {
			if (send(j, recv_buf, nbytes_recvd, 0) == -1) {
				perror("send");
			}
		}
	}
}
		
void Server::send_recv(int i, fd_set *master, int sockfd, int fdmax)
{
	int nbytes_recvd, j;
	char recv_buf[BUFSIZE];

	// If message received, send except i
	if ((nbytes_recvd = recv(i, recv_buf, BUFSIZE, 0)) <= 0) {
		if (nbytes_recvd == 0) {
			printf("socket %d hung up\n", i);
		}else {
			perror("recv");
		}
		close(i);
		FD_CLR(i, master);
	} else { 
		
		std::string sockfd_string = "";

		// auto senderPtr = onlineClient.find(i);
		// sockfd_string = sockfd_string + (senderPtr->second).getId();

		sockfd_string = std::to_string(i);
		sockfd_string = "Socket No " + sockfd_string;

		sockfd_string = sockfd_string + " : " + std::string(recv_buf, nbytes_recvd);

		char* sockfd_char = new char[sockfd_string.length() + 1];
		strcpy(sockfd_char, sockfd_string.c_str());

		// auto itr = onlineClient.find(i);
		// room = (itr->second).getRoomNo();	

		// auto iterator = roomClient.find(room);	
		// for(int so : iterator->second){
		// 	send_to_room(so, i, sockfd, strlen(sockfd_char), sockfd_char, master);
		// }

		for(j = 0; j <= fdmax; j++){
			send_to_all(j, i, sockfd, strlen(sockfd_char), sockfd_char, master);
		}
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
		// fdmax == total number of sockets
		if(newsockfd > *fdmax){
			*fdmax = newsockfd;
		}
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

void Server::tcpListener(int sockfd, int fdmax, int i, struct sockaddr_in my_addr, struct sockaddr_in client_addr, fd_set master, fd_set read_fds)
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
		
		for (i = 0; i <= fdmax; i++){
			if (FD_ISSET(i, &read_fds)){
				if (i == sockfd)
					connection_accept(&master, &fdmax, sockfd, &client_addr);
				else
					send_recv(i, &master, sockfd, fdmax);
			}
		}
	}

}

void Server::enterLounge(int sockfd)
{
	auto itr = roomClient.find(0);		// Lounge room number == 0
	if(itr != roomClient.end()){		
		(itr->second).push_back(sockfd);
	} else {
		std::list<int> new_lounge = {sockfd};
		roomClient.emplace(0, new_lounge);
	}
	auto it = onlineClient.find(sockfd);
	(it->second).setRoomNo(0);
	cout << "Entered Lounge" << endl;
}

void Server::send_to_room(int j, int i, int sockfd, int nbytes_recvd, char *recv_buf, fd_set *master)
{
	if (FD_ISSET(j, master)){
		if (j != sockfd && j != i) {
			if (send(j, recv_buf, nbytes_recvd, 0) == -1) {
				perror("send");
			}
		}
	}
}

// void Server::insertClientInfo(ClientInfo clientInfo) {
// 	//int opt = client.getOption();
// 	int opt = 1;
// 	if(opt == 1){
// 	
// 		clientInfo_list.push_back(clientInfo);
// 		cout << "list size: " << clientInfo_list.size() << endl;
// 		//test
// 		for(ClientInfo ci :  clientInfo_list) {
// 			cout << "client id: " << ci.getId() << endl;
// 		}
// 	} else if(opt == 2){
// 		ClientInfo recv_clientInfo = clientInfo;
// 		for(ClientInfo ci : clientInfo_list) {
// 			if(ci.getId() == recv_clientInfo.getId() && ci.getPassword() == recv_clientInfo.getPassword()) {
// 				cout << "Login succeeded" << endl;
// 				break;
// 			}
// 		}
// 		cout << "Login failed" << endl;
// 	} else {
// 		cout << "Exit like you chose" << endl;
// 		exit(4);
// 	}
// 	
// }
// 
int main(int argc, char* argv[])
{

	fd_set master;
	fd_set read_fds;
	int fdmax, i;
	int sockfd = 0;
	struct sockaddr_in my_addr, client_addr;

	Server server;
	server.tcpListener(sockfd, fdmax, i, my_addr, client_addr, master, read_fds);
	return 0;
}





