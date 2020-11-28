#ifndef ROOM
#define ROOM

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <cstring>
#include <cstdint>
#include <iostream>
#include <list>
#include "clientInfo.h"

/**
CLASS STRUCTURE
Room (
  -ChatRoom
  -Lounge
**/


class Room {

public: 
	
	Room();
	Room(int RoomNo);
	~Room();

	virtual void enter(ClientInfo clientInfo);
	virtual void exit (ClientInfo clientInfo);
	virtual void enterExitMessage(ClientInfo clientInfo, bool entrance);

protected:

	int RoomNo;
	ClientInfo clientInfo;
	std::list<ClientInfo> clientInfo_list;

};

class ChatRoom : public Room {

public:

	ChatRoom();													// Constructor
	ChatRoom(int const RoomNo);

	~ChatRoom();												// Deconstructor

	int numberOfClient();								

private:

	int const RoomNo;
	char* message;
	std::list<ClientInfo> clientInfo_list;					// clientList for chatroom

	void sendMessage(ClientInfo clientInfo, char* message);			// Send messages
	void printClientList();									// Shows clients in this chatroom
	int numOfClient = clientInfo_list.size();

};

class Lounge : public Room {

public:

	Lounge();
	~Lounge();

    void printClientList();                             										// Shows clients in this chatroom
    int numberOfClient();

private:	
	std::list<ClientInfo> clientInfo_list;
	int numOfClient = clientInfo_list.size();						
};

#endif
