#include <iostream>
#include <string>

class createLogin 
{
public:
	Client askClient(std::list<Client> client_list);
	void createAccount(string id, string password);
	void login(string id, string password);
private:
	string id, password;
	// This is suppoed to create Client
	Client client;
}
