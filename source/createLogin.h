#include <iostream>
#include <string>
#include <list>
#include "clientInfo.h"

class createLogin 
{
public:
	ClientInfo askClient(std::list<ClientInfo> clientInfo_list);
	void createAccount(std::string id, std::string password);
	void login(std::string id, std::string password);
private:

	createLogin();
	~createLogin();

	std::string id, password;
	ClientInfo clientInfo;
	std::list<ClientInfo>clientInfo_list;
};
