#include "room.h"

using namespace std;

void Room::enter(ClientInfo clientInfo)
{
	for(ClientInfo ci : clientInfo_list) {
		if(ci.getId() == clientinfo.getId() {
			cout << "You cannot join the room. Same username exists" << endl;
		}
		exit(0);
	}
	clientInfo_list.push_back(clientInfo);
	enterExitMessage(clientInfo, true);
};

void Room::exit(ClientInfo clientInfo)
{
	enterExitMessage(clientInfo, false);
	for(ClientInfo ci : clientInfo_list) {
		if(ci.getId() == clientInfo.getId()) {
			clientInfo_list.erase(clientInfo);
		}	
		break;
	}
};

void Room::enterExitMessage(ClientInfo clientInfo, bool entrance)
{
	switch(entrance) {
		case true:
			std::cout << clientInfo.getId() << " joined the chat";
			break;
		case false:
			std::cout << clientInfo.getId() << " left the chat";
			break;
	}
};
// 
// void Room::connection_accept(fd_set* master, int* fdmax, int sockfd, struct sockaddr_in* client_addr)
// {
// 	socklen_t addrlen;
// 	int newsockfd;
// 	
// 	addrlen = sizeof(struct sockaddr_in);
// 	if((newsockfd = accept(sockfd,(struct sockaddr*)client_addr, &addrlen)) == -1) {
// 		perror("accept");
// 		exit(1);
// 	} else {
// 		FD_SET(newsockfd, master);
// 		if (newsockfd > *fdmax) {
// 			*fdmax = newsockfd;
// 		}
// 
// 
// 	}
// 
// };
