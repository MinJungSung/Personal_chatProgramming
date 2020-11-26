#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <pthread.h>
#include <cstdint>
#include <iostream>
#include <list>
#include "server.cpp"
#include "client.cpp"
#include "room.cpp"

// TODO: Should I include "room.h" as well?
// TODO: Make sure that these functions inherit from Room

ChatRoom::ChatRoom(int const RoomNo)
{
	this->RoomNo = RoomNo;
}

virtual void ChatRoom::enter(Client client){};
virtual void ChatRoom::exit (Client client){};
virtual void ChatRoom::enterExitMessage(Client client){};

void ChatRoom::printClientList() 
{
	if (numOfClient == 0) {
		"There is no one in this room"
	} else {
		cout << "Client List in Lounge \n";
		for (Client client : client_list) {
			cout << "Client " << client.toString() << " \n";
		}

	}
};

int ChatRoom::numberOfClient() 
{
	return numOfClient;
};
