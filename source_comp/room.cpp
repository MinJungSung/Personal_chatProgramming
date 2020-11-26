#include "room.h"

void Room::enter(clsClient client)
{
	//bool foundClient = (std::find(client_list.begin(), client_list.end(), client) != client_list.end());
	//if (foundClient) {
	if (true) {
		throw std::invalid_argument("Client number already exists \n");
	} else {
		//client_list.push_back(client);
		enterExitMessage(client, true);
	}
};

void Room::exit(clsClient client)
{
	//std::list<Client>::iterator clientListItr = std::find(client_list.begin(), client_list.end(), client);
	//if (clientListItr != client_list.end()) {
	//	client_list.erase(clientListItr);
	//	enterExitMessage(client, false);
	//} else {
	//	throw invalid_argument("Client doesn't exist in the room \n");
	//}
};

void Room::enterExitMessage(clsClient client, bool entrance)
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

