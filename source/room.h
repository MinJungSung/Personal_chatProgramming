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

	// virtual void enter(ClientInfo clientInfo);
	// virtual void exit (ClientInfo clientInfo);
	// virtual void enterExitMessage(ClientInfo clientInfo, bool entrance);

	void enter(ClientInfo clientInfo);
	void exit (ClientInfo clientInfo);
	void enterExitMessage(ClientInfo clientInfo, bool entrance);

private:

	int RoomNo;
	ClientInfo clientInfo;
	std::list<ClientInfo> clientInfo_list;

};

class ChatRoom : public Room {

public:

	ChatRoom();													// Constructor
	ChatRoom(int const RoomNo);

	~ChatRoom();												// Deconstructor
	
	void enter(ClientInfo clientInfo);
	void exit(ClientInfo clientInfo);
	void enterExitMessage(ClientInfo clientInfo, bool entrance);	
	int numberOfClient();								

private:

	int const RoomNo;
	int numOfClient = clientInfo_list.size();
	std::string message;	
	std::list<ClientInfo> clientInfo_list;					// clientList for chatroom

	void sendMessage(ClientInfo clientInfo, std::string message);			// Send messages
	void printClientList();									// Shows clients in this chatroom

};

class Lounge : public Room {

public:

	Lounge();
	~Lounge();

	void enter(ClientInfo clientInfo);
	void exit(ClientInfo clientInfo);
	void enterExitMessage(ClientInfo clientInfo, bool entrance);	
    void printClientList();                             										// Shows clients in this chatroom
    int numberOfClient();

private:	

	ClientInfo clientInfo;	
	std::list<ClientInfo> clientInfo_list;
	int numOfClient = clientInfo_list.size();						
};

#endif
