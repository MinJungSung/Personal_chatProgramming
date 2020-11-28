#include "room.h"

void Room::enter(ClientInfo clientInfo)
{
	enterExitMessage(clientInfo, true);
};

void Room::exit(ClientInfo clientInfo)
{
	enterExitMessage(clientInfo, false);
};

void Room::enterExitMessage(ClientInfo clientInfo, bool entrance)
{
	switch(entrance) {
		case true:
			std::cout << "Client " << clientInfo.getId() << " joined the chat";
			break;
		case false:
			std::cout << "Client " << clientInfo.getId() << " left the chat";
			break;
	}
};

