#include "clientInfo.h"

void ClientInfo::setId(std::string id)
{
	this->id = id;
}

void ClientInfo::setPassword(std::string password)
{
	this->password = password;
}

void ClientInfo::setRoomNo(int roomNo)
{
	this->roomNo = roomNo;
}

std::string ClientInfo::getId()
{
	return id;
}

std::string ClientInfo::getPassword()
{
	return password;
}

int ClientInfo::getRoomNo()
{
	return roomNo;
}
