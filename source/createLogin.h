#include <iostream>
#include <string>
#include <list>
#include "clientInfo.h"

class createLogin 
{
public:
	ClientInfo askClient();
	void createAccount(std::string id, std::string password);
	void login(std::string id, std::string password);
private:

	createLogin();
	~createLogin();

	std::string id, password;
	ClientInfo clientInfo;
};
