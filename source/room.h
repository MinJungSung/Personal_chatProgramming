#ifndef ROOM
#define ROOM

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <cstdint>
#include <iostream>
#include <list>
#include "clientInfo.h"
#include "server.h"

/**
CLASS STRUCTURE
Room (
  -ChatRoom
  -Lounge
**/


class Room {

public: 
	
	Room();
	~Room();

	void enter(ClientInfo clientInfo);
	void exit (ClientInfo clientInfo);
	void enterExitMessage(ClientInfo clientInfo, bool entrance);
	// void connection_accept(fd_set* master, int* fdmax, int sockfd, struct sockaddr_in* client_addr);

private:

	int RoomNo;
	ClientInfo clientInfo;
	std::list<ClientInfo> clientInfo_list;

	// fd_set master;
	// fd_set read_fds;
	// int fdmax, i;
	// int sockfd = 0;
	// struct sockaddr_in client_addr;

};

class ChatRoom : public Room {

public:

	ChatRoom();													// Constructor
	ChatRoom(int const RoomNo);

	~ChatRoom();												// Deconstructor
	
	void enter(ClientInfo clientInfo);
	void exit(ClientInfo clientInfo);
	void enterExitMessage(ClientInfo clientInfo, bool entrance);
	void connection_accept(fd_set* master, int* fdmax, int sockfd, struct sockaddr_in* client_addr);
	
	int numberOfClient();								

private:

	int const RoomNo;
	int numOfClient = clientInfo_list.size();
	std::string message;	
	std::list<ClientInfo> clientInfo_list;					// clientList for chatroom

	void sendMessage(ClientInfo clientInfo, std::string message);			// Send messages
	void printClientList();									// Shows clients in this chatroom

	fd_set master;
	fd_set read_fds;
	int fdmax, i;
	int sockfd = 0;
	struct sockaddr_in client_addr;

};

class Lounge : public Room {

public:

	Lounge();
	~Lounge();

	void enter(ClientInfo clientInfo);
	void exit(ClientInfo clientInfo);
	void enterExitMessage(ClientInfo clientInfo, bool entrance);	
	void connection_accept(fd_set* master, int* fdmax, int sockfd, struct sockaddr_in* client_addr);

    void printClientList();                             										// Shows clients in this chatroom
    int numberOfClient();

	// TODO: Create a chatoom or join a chatroom
	// Need to have a list of chatroom to join
	// create -> add to chatroom list (remove the following client and add to the room's clientInfoList)
	// join -> loop through chatroom list and join if it exists (remove the following client and add to the room's clientInfoList)

private:	

	ClientInfo clientInfo;	
	std::list<ClientInfo> clientInfo_list;
	std::list<ChatRoom> chatRoom_list;
	int numOfClient = clientInfo_list.size();						

	fd_set master;
	fd_set read_fds;
	int fdmax, i;
	int sockfd = 0;
	struct sockaddr_in client_addr;

};

#endif
