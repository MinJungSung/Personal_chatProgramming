#include "createLogin.h"

using namespace std;

ClientInfo createLogin::askClient(list<ClientInfo> clientInfo_list)
{
	int option;
	this->clientInfo_list = clientInfo_list;
	cout << "Do you want to (1)create an account,(2)login, or (3)exit?";
	cin >> option;
	cout << endl;
	switch(option) {
		case 1:
			cout << "ID: ";
			cin >> id;
			cout << endl;
			cout << "Password: ";
			cin >> password;
			cout << endl;
			createLogin::createAccount(id, password);
			break;
		case 2:
			cout << "ID: ";
			cin >> id;
			cout << endl;
			cout << "Password: ";
			cin >> password;
			cout << endl;
			createLogin::login(id, password);
			cout << "You are successfully logged in" << endl;
			break;
		case 3:
			cout << "Exit" << endl;
			exit(0);
		default:
			createLogin::askClient(clientInfo_list);
	}
	return clientInfo;
};

void createLogin::createAccount(string id, string password)
{
	for(ClientInfo ci : clientInfo_list) {
		if(ci.getId() == id) {
			cout << "Same ID already exists" << endl;
			createLogin::askClient(clientInfo_list);
			break;
		}
	}
	clientInfo.setId(id);
	clientInfo.setPassword(password);
	clientInfo_list.push_back(clientInfo);
	cout << "Your account is successfully created" << endl;

};

void createLogin::login(string id, string password)
{
	// Loop through clientList and find the same id and password
	// client = found_client
	for(ClientInfo ci :  clientInfo_list) {
		if(clientInfo.getId() == id && clientInfo.getPassword() == password) {	
			cout << "You are successfully loggine in" << endl;
			clientInfo = ci;
			break;	
		} else if (clientInfo.getId() == id && clientInfo.getPassword() != password) {
			cout << "Your password is incorrect" << endl;
			createLogin::askClient(clientInfo_list);
			break;
		} 
	}
	cout << "Your account doesn't exist" << endl;
	createLogin::askClient(clientInfo_list);
};
