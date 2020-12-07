#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdint>
#include <iostream>
#include <list>
#include "room.h"

// TODO: Should I include "room.h" as well?
// TODO: Make sure that these functions inherit from Room


using namespace std;

void ChatRoom::enter(ClientInfo clientInfo){
	Room::enter(clientInfo);
};

void ChatRoom::exit (ClientInfo clientInfo){
	Room::exit(clientInfo);
};

void ChatRoom::enterExitMessage(ClientInfo clientInfo, bool entrance){
	Room::enterExitMessage(clientInfo, entrance);
};

void sendMessage(ClientInfo clientInfo, std::string message) {
	cout << clientInfo.getId() << " : " << message << endl;
};

void ChatRoom::printClientList() 
{
	if (numOfClient == 0) {
		cout << "There is no one in this room" << endl;
	} else {
		cout << "Client List in Lounge \n";
		for (ClientInfo clientInfo : clientInfo_list) {
			cout <<  clientInfo.getId() << " \n";
		}

	}
};

int ChatRoom::numberOfClient() 
{
	return numOfClient;
};
