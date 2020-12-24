#include "requestHandler.h"

using namespace std;

void RequestHandler::RequestHandler(int sockfd, fd_set* master){
	this->sockfd = sockfd;
	this->master = master;
}

void RequestHandler::requestDispatcher(int sender, string request){
	this->request = request;
	this->sender = sender;
	if((request.substr(0,18)).compare("clientInformation:") == 0){
		clientInformation(sender, request);
	} else if((request.substr(0,10)).compare("createRoom") == 0){
		createRoom(sender);
	} else if((request.substr(0,8)).compare("exitRoom") == 0){
		exitRoom(sender);
	} else if((request.substr(0,8)).compare("joinRoom") == 0){
		joinRoom(sender);
	} else if((request.substr(0,8)).compare("showRoom") == 0){
		showRoom(sender);
	} else {
		message(sender);
	}
}

void RequestHandler::clientInformation(int sender, string request){
	string requestWithoutPrefix = request.substr(18);
	if(clientList.create(sender, requestWithoutPrefix)){
		roomList.increaseNum(LOUNGE);
	}
}
	
void RequestHandler::createRoom(int sender){
	if(clientList.getClientInfo(sender, ROOMNUMBER) == LOUNGE){
		messageHandler.sendToSender(sockfd, master, sender, "You are already in the chat\n");
	} else {
		int createdRoom = roomList.createRoom();
		roomList.decreaseNum(LOUNGE);
		if(clientList.changeClient(sender, ROOMNUMBER, to_string(createdRoom))){
			messageHandler.sendToSender(sockfd, master, sender, "You successfully created a room\n");
		}
	}
}

void RequestHandler::exitRoom(int sender){
	if(clientList.getClientInfo(sender, ROOMNUMBER) == LOUNGE){
		messageHandler.sendToSender(sockfd, master, sender, "You are already in the lounge\n");
	} else {
		int originalRoom = stoi(clientList.getClientInfo(sender, ROOMNUMBER));
		if(clientList.changeClient(sender,ROOMNUMBER,to_string(LOUNGE))){
			roomList.decreaseNum(orginalRoom);
			roomList.increaseNum(LOUNGE);
			messageHandler.sendToSender(sockfd, master, sender, "You left the chat\n");
			if(roomList.findNum(originalRoom) > 0){
				string leaveMessage = clientList.getClientInfo(sender, USERNAME) + " left the chat\n";
				messageHandler.sendToOthersInRoom(sockfd, master, sender, clientList.sendTo(sender), leaveMessage);
			}
		}
	}
}


void RequestHandler::showRoom(int sender){
	string roomString = roomList.showRoom(); 
	messageHandler.sendToSender(sockfd, master, sender, roomString);
}

void RequestHandler::joinRoom(int sender){
	//sendToSender askWhichRoom
	string askWhichRoom = "Which room do you want to join?\n";
	messageHandler.sendToSender(sockfd, master, sender, askWhichRoom);

	int room_nbytes_recvd;
	char room_recv_buf[BUFSIZE];
	//connection fails
	if((room_nbytes_recvd = recv(sender, room_recv_buf, sizeof(room_recv_buf) - 1, 0)) <= 0){
		if(room_nbytes_recvd == 0){
			printf("socket %d hung up\n", i);
		} else {	
			printf("recv");
		}
		disconnected(sender);	
	//Received answer
	} else if(room_nbytes_recvd > 1) {
		string room_recv_buf_toString(room_recv_buf);
		trim(room_recv_buf_toString);
	
		if(!roomList.findRoom(stoi(room_recv_buf_toString))){
			string resultMessage = "Sorry, you put incorrect room number\n";
			messageHandler.sendToSender(sockfd, master, sender, resultMessage);
		} else {
			int originalRoom = clientList.getClientInfo(sender,ROOMNUMBER);
			if(clientList.changeClient(sender,ROOMNUMBER,room_recv_buf_toString)){
				string resultMessage = "You successfully joined the chat\n";
				messageHandler.sendToSender(sockfd, master, sender, resultMessage);
				roomList.decreaseNum(originalRoom);

				string leaveMessage = clientList.getClientInfo(sender,USERNAME) + " left the chat\n";
				messageHandler.sendToOthersInRoom(sockfd, master, sender, clientList.sendTo(sender), leaveMessage);
				roomList.increaseNum(room_recv_buf_toString);
			}
		}
	}
}

void RequestHandler::message(int sender){
	messageHandler.sendToOthersInRoom(sockfd, master, sender, clientList.sendTo(sender), request);
}

void RequestHandler::connectionHandler(int sender, string request){	
	this->sender = sender;
	this->request = request;
	if((request.substr(0,9)).compare("connected") == 0){
		connected(sender);
	} else if((request.substr(0,12)).compare("disconnected") == 0){
		disconnected(sender);
	}
}

void RequestHandler::connected(int sender){
	

}

void RequestHandler::disconnected(int sender){
	int originalRoom = stoi(clientList.getClientInfo(sender,ROOMNUMBER));
	roomList.decreaseNum(originalRoom);
	if(roomList.findNum(originalRoom) != 0 && originalRoom != LOUNGE){
		string leaveMessage = clientList.getClientInfo(sender,USERNAME) + " left the chat\n";
		messageHandler.sendToOthersInRoom(sockfd, master, sender, clientList.sendTo(sender), leaveMessage);
	}
	clientList.disconnect(sender);
} 
