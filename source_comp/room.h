#ifndef ROOM
#define ROOM

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <pthread.h>
#include <cstdint>
#include <iostream>
#include <list>
#include "clsClient.h"

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

	virtual void enter(clsClient client);
	virtual void exit (clsClient client);
	virtual void enterExitMessage(clsClient client, bool entrance);

protected:

	int RoomNo;
	clsClient* client;
	std::list<clsClient> client_list;

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
	std::list<clsClient> client_list;						// Add clients here whenever new client comes in through Enter(client);

	void sendMessage(clsClient client, char* message);			// Send messages
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
	std::list<clsClient> client_list;
	int numOfClient = client_list.size();						
};

#endif
