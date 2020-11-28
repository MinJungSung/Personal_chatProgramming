#include "clientInfo.h"

void ClientInfo::setId(std::string id)
{
	this->id = id;
}

void ClientInfo::setPassword(std::string password)
{
	this->password = password;
}

std::string ClientInfo::getId()
{
	return id;
}

std::string ClientInfo::getPassword()
{
	return password;
}
