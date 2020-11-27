#ifndef ROOM
#define ROOM

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <cstring>
#include <pthread.h>
#include <algorithm>
#include <ifstream>
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <list>
#include "server.h"
#include "client.h"

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

	virtual void enter(Client client);
	virtual void exit (Client client);
	virtual void enterExitMessage(Client client, bool entrance);

protected:

	int RoomNo;
	Client* client;
	std::list<Client> client_list;

};

class ChatRoom : public Room {

public:

	ChatRoom();													// Constructor
	ChatRoom(int const RoomNo);

	~ChatRoom();												// Deconstructor

	//virtual void enter(Client client);							// This adds a client to the room
	//virtual void exit (Client client);							// This removes a client from the room
	//virtual void enterExitMessage(Client client);				// This says welcome and goodbye message when the client enters and exits
	int numberOfClient();								

private:

	int const RoomNo;
	char* message;
	std::list<Client> client_list;						// Add clients here whenever new client comes in through Enter(client);

	void sendMessage(Client client, char* message);			// Send messages
	void printClientList();									// Shows clients in this chatroom
	int numOfClient = client_list.size();

};

class Lounge : public Room {

public:

	Lounge();
	~Lounge();

    //virtual void enter(Client client);                          // This adds a client to the room
    //virtual void exit (Client client);                          // This removes a client from the room
    //virtual void enterExitMessage(Client client);               // This says welcome and goodbye message when the client enters and exits
    void printClientList();                             										// Shows clients in this chatroom
    int numberOfClient();

private:	
	std::list<Client> client_list;
	int numOfClient = client_list.size();						
};

#endif
