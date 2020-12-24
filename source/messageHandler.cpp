#include "messageHandler.h"

using namespace std;

void MessageHandler::sendToSender(int sockfd, fd_set* master, int sender, string message){
	char* sockfd_char = new char[message.length() + 1];
	strcpy(sockfd_char, message.c_str());
	if(FD_ISSET(sender, master)){
		if(send(sender, sockfd_char, strlen(sockfd_char), 0) == -1){
			perror("send");
		}
	}
}

//TODO:Think of a way to make this as a template
void MessageHandler::sendToAll(int sockfd, fd_set* master, int sender, map<int,ClientInfo> receiver, string message){
	char* sockfd_char = new char[message.length() + 1];
	strcpy(sockfd_char, message.c_str());
	map<int,ClientInfo>::iterator it;
	for(it = receiver.begin(); it != receiver.end(); ++it){
		if(FD_ISSET(it->first, master) && it->first != sender){
			if(send(it->first, sockfd_char, strlen(sockfd_char), 0) == -1){
				perror("send");
			}
		}
	}
}

void MessageHandler::sendToOthersInRoom(int sockfd, fd_set* master, int sender, vector<int> receiver, string message){
	char* sockfd_char = new char[message.length() + 1];
	strcpy(sockf_char, message.c_str());
	vector<int>::iterator it;
	for(it = receiver.begin(); it != receiver.end(); ++it){
		if(FD_ISSET(it->first, master) && it->first != sender){
			if(send(it->first, sockfd, strlen(sockfd_char), 0) == -1){
				perror("send");
			}
		}
	}
}
