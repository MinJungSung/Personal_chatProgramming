#ifndef ROOM
#define ROOM

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <cstdint>
#include <iostream>
#include <list>
#include <algorithm>
#include "server.cpp"
#include "client.cpp"
#include "room.h"
#include "errorHandler.cpp"

// TODO: if errorHandler contains some libraries, does that inherit to the current cpp file as well?
// TODO: Make sure that the constructor works
// // If Room is created without RoomNo, create Lounge
// Room::Room() 
// {
// 	Lounge* lounge;
// }
// 
// // If Room is created with RoomNo, create ChatRoom with RoomNo
// Room::Room(int RoomNo);
// {
// 	ChatRoom* chatRoom(RoomNo);
// }

virtual void Room::enter(Client client)
{
	bool foundClient = (std::find(client_list.begin(), client_list.end(), client) != client_list.end());
	if (foundClient) {
		std::set_unexpected(errorHandler::room_unexp);
		try {
			errorHandler::room_bad_exception();
		} catch(const std::bad_exception& e) {
			std::cerr << "Caught " << e.what() << "\n";
		}

	} else {
		client_list.push_back(client);
		enterExitMessage(client, true);
	}
};

virtual void Room::exit(Client client) 
{	
	std::list<Client>::iterator clientListItr = std::find(client_list.begin(), client_list.end(), client);
	if (clientListItr != client_list.end()) {
		client_list.erase(clientListItr);
		enterExitMessage(client, false);
	} else {
		std::set_unexpected(errorHandler::room_unexp);
		try {
			errorHandler::room_bad_exception();
		} catch(const std::bad_exception& e) {
			std::cerr << "Caught " << e.what() << "\n";
		}
	}
};

virtual void Room::enterExitMessage(Client client, bool entrance)
{
	switch(entrance) {
		case true:
			std::cout << "Client " << client.toString() << " joined the chat";
			break;
		case false:
			std::cout << "Client " << client.toString() << " left the chat";
			break;
	}
};

#endif
