#include "messageHandler.h"

using namespace std;

void MessageHandler::sendTo(fd_set* master, int sender, vector<int> receiver, int messageChoice, string param){

	string message = printMessage(messageChoice, param);

	char* sockfd_char = new char[message.length() + 1];
	strcpy(sockfd_char, message.c_str());
	
	if(receiver.size() == 1){
		if(FD_ISSET(sender, master)){
			if(send(sender, sockfd_char, strlen(sockfd_char), 0) == -1){
				perror("send");
			}
		}
	} else {
		vector<int>::iterator it;
	
		for(it = receiver.begin(); it != receiver.end(); ++it){
			if(FD_ISSET(*it, master) && *it != sender){
				if(send(*it, sockfd_char, strlen(sockfd_char), 0) == -1){
					perror("send");
				}
			} 	
		}
	}
}

