#include "createLogin.h"

Client createLogin::askClient(std::list<Client> client_list)
{
	int option;
	cout << "Do you want to (1)create an account,(2)login, or (3)cancel?";
	cin >> option;
	cout << endl;
	switch(option) {
		case 1:
			string id, password;
			cout << "ID: ";
			cin >> id;
			cout << endl;
			cout << "Password: ";
			cin >> password;
			cout << endl;
			createLogin::createAccount(string id, string password);
			cout << "Your account is successfully created" << endl;
			break;
		case 2:
			string id, password;
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
			break;
		default:
			Client createLogin::askClient(client_list);
	}
	return client;
};

Client createLogin::createAccount(string id, string password)
{
	// client = new Client?
	// set id and password

};

Client createLogin::login(string id, string password)
{
	// Loop through clientList and find the same id and password
	// client = found_client

};
