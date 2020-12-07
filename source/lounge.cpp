#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <cstdint>
#include <iostream>
#include "room.h"

// 
// ChatRoom::ChatRoom(int const RoomNo)
// {
// 	this->RoomNo = RoomNo;
// }

using namespace std;

void Lounge::enter(ClientInfo clientInfo){
	Room::enter(clientInfo);
};

void Lounge::exit (ClientInfo clientInfo){
	Room::exit(clientInfo);
};

void Lounge::enterExitMessage(ClientInfo clientInfo, bool entrance){
	Room::enterExitMessage(clientInfo, entrance);
};

void Lounge::printClientList() 
{
	if (numOfClient == 0) {
		cout << "There is no one in this room";
	} else {
		cout << "Client List in Lounge\n";
		for (ClientInfo clientInfo : clientInfo_list) {
			cout << clientInfo.getId() << " \n";
		}
	}
};

int Lounge::numberOfClient() 
{
	return numOfClient;
};
