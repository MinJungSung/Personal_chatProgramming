#include <iostream>
#include <string>
#include <list>
#include "clientInfo.h"

class CreateLogin
{
public:

	//ClientInfo askClient(std::list<ClientInfo> clientInfo_list);
	int askClient();
	void getSetCredential();
	void createClientInfo();
	void findClientInfo();
	ClientInfo getClientInfo();
	std::list<ClientInfo> getClientInfoList();

	//void createAccount(std::string id, std::string password);
	//void login(std::string id, std::string password);
private:

	std::string id, password; 
	int option;
	ClientInfo clientInfo;
	std::list<ClientInfo> clientInfo_list;
};
