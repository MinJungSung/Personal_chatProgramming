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


/**
CLASS STRUCTURE
Room (
  -ChatRoom
  -Lounge
**/


class Room {

public: 
	
	Room();		// Constructor
	~Room();	// Deconstructor


	virtual void enter(Client client);
	virtual void exit (Client client);
	virtual void enterExitMessage(Client client);

protected:

	Client* client;

};

class ChatRoom : public Room {

public:

	ChatRoom();													// Constructor
	ChatRoom(int const RoomNo);

	~ChatRoom();												// Deconstructor

	virtual void enter(Client client);							// This adds a client to the room
	virtual void exit (Client client);							// This removes a client from the room
	virtual void enterExitMessage(Client client);				// This says welcome and goodbye message when the client enters and exits
	virtual void sendMessage(Client client, char* message);		// Send messages
	virtual void printClientList();								// Shows clients in this chatroom
	virtual int numberOfClient();								

private:
	int const RoomNo;
	char* message;
	std::list<Client> client_list_inRoom;						// Add clients here whenever new client comes in through Enter(client);
};

class Lounge : public Room {

public:

	Lounge();
	~Lounge();

    virtual void enter(Client client);                          // This adds a client to the room
    virtual void exit (Client client);                          // This removes a client from the room
    virtual void enterExitMessage(Client client);               // This says welcome and goodbye message when the client enters and exits
    virtual void printClientList();                             // Shows clients in this chatroom
    virtual int numberOfClient();

private:	
	std::list<Client> client_list_inLounge;						
};
