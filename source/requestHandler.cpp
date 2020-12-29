#include "requestHandler.h"

using namespace std;

RequestHandler::RequestHandler(){

}

void RequestHandler::setDefault(int sockfd, fd_set* master){
	this->sockfd = sockfd;
	this->master = *master;
}

void RequestHandler::requestDispatcher(int sender, string request){
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
	} else if((request.substr(0,9)).compare("connected") == 0){
		connected(sender);
	} else if((request.substr(0,12)).compare("disconnected") == 0){
		disconnected(sender);
	} else {
		message(sender, request);
	}
}

void RequestHandler::clientInformation(int sender, string request){

	string requestWithoutPrefix = request.substr(18);
	clientList.create(sender, requestWithoutPrefix);
}
	
void RequestHandler::createRoom(int sender){

	if(stoi(clientList.getClientInfo(sender, ROOMNUMBER)) != LOUNGE){
		messageHandler.sendTo(&master, sender, {sender}, 7, "");
	} else {
		int createdRoom = roomList.createRoom();
		roomList.decreaseNum(LOUNGE);
		if(clientList.changeClient(sender, ROOMNUMBER, to_string(createdRoom))){
			messageHandler.sendTo(&master, sender, {sender}, 0, "");
		}
	}
}

void RequestHandler::exitRoom(int sender){

	if(stoi(clientList.getClientInfo(sender, ROOMNUMBER)) == LOUNGE){
		messageHandler.sendTo(&master, sender, {sender}, 8, "");
	} else {
		int originalRoom = stoi(clientList.getClientInfo(sender, ROOMNUMBER));
		if(clientList.changeClient(sender,ROOMNUMBER,to_string(LOUNGE))){
			roomList.decreaseNum(originalRoom);
			roomList.increaseNum(LOUNGE);
			messageHandler.sendTo(&master, sender, {sender}, 2, "");
		}
		if(roomList.findNum(originalRoom) > 0){
			messageHandler.sendTo(&master, sender, clientList.sendTo(sender), 4, clientList.getClientInfo(sender, USERNAME));
		}
	}
}


void RequestHandler::showRoom(int sender){
	messageHandler.sendTo(&master, sender, {sender}, 10, roomList.showRoom());
}

void RequestHandler::joinRoom(int sender){
	messageHandler.sendTo(&master, sender, {sender}, 6, "");

	int room_nbytes_recvd;
	char room_recv_buf[BUFSIZE];

	if((room_nbytes_recvd = recv(sender, room_recv_buf, sizeof(room_recv_buf) - 1, 0)) <= 0){
		if(room_nbytes_recvd == 0){
			printf("socket %d hung up\n", sender);
		} else {	
			printf("recv");
		}
		disconnected(sender);	

	} else if(room_nbytes_recvd > 1) {
		string room_recv_buf_toString(room_recv_buf);
		trim(room_recv_buf_toString);
	
		if(!roomList.findRoom(stoi(room_recv_buf_toString))){
			messageHandler.sendTo(&master, sender, {sender}, 5, room_recv_buf_toString);
		} else {
			int originalRoom = stoi(clientList.getClientInfo(sender,ROOMNUMBER));
			if(clientList.changeClient(sender,ROOMNUMBER,room_recv_buf_toString)){
				messageHandler.sendTo(&master, sender, {sender}, 1, "");
				roomList.decreaseNum(originalRoom);
				if(roomList.findNum(originalRoom) > 0){
					messageHandler.sendTo(&master, sender, clientList.sendTo(sender), 4, clientList.getClientInfo(sender, USERNAME));
				}
				roomList.increaseNum(stoi(room_recv_buf_toString));
			}
		}
	}
}

void RequestHandler::connected(int sender){
	roomList.increaseNum(LOUNGE);
}

void RequestHandler::disconnected(int sender){
	int originalRoom = 0;
	originalRoom = stoi(clientList.getClientInfo(sender,ROOMNUMBER));

	roomList.decreaseNum(originalRoom);
	if(roomList.findNum(originalRoom) != 0 && originalRoom != LOUNGE){
		messageHandler.sendTo(&master, sender, clientList.sendTo(sender), 4, clientList.getClientInfo(sender, USERNAME));
	}
	clientList.disconnect(sender);
} 

void RequestHandler::message(int sender, string request){
	messageHandler.sendTo(&master, sender, clientList.sendTo(sender), 10, clientList.getClientInfo(sender, USERNAME) + ":" + request);
	cout << "Request: " << request << endl;
}


