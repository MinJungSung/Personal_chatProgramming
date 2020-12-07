#include "createLogin.h"

using namespace std;

// Accept clientInfo_list only to check whether the account exists or not
// ClientInfo CreateLogin::askClient(std::list<ClientInfo> clientInfo_list)
// {
// 	int option;
// 	cout << "Do you want to (1)create an account,(2)login, or (3)exit?";
// 	cin >> option;
// 
// 	this->clientInfo_list =  clientInfo_list;
// 
// 	switch(option) {
// 		case 1:
// 			cout << "ID: ";
// 			cin >> id;
// 			cout << "Password: ";
// 			cin >> password;
// 			CreateLogin::createAccount(id, password);
// 			break;
// 		case 2:
// 			cout << "ID: ";
// 			cin >> id;
// 			cout << "Password: ";
// 			cin >> password;
// 			CreateLogin::login(id, password);
// 			cout << "You are successfully logged in" << endl;
// 			break;
// 		case 3:
// 			cout << "Exit" << endl;
// 			exit(0);
// 		default:
// 			CreateLogin::askClient(clientInfo_list);
// 	}
// 	return clientInfo;
// }

int CreateLogin::askClient()
{
	cout << "Do you want to (1)create an account,(2)login, or (3)exit?";
	cin >> option;
	return option;
}

void CreateLogin::getSetCredential()
{
	cout << "ID: ";
	cin >> id;
	cout << "Password: ";
	cin >> password;
}

void CreateLogin::createClientInfo()
{
	ClientInfo clientInfo;
	clientInfo.setId(id);
	clientInfo.setPassword(password);	
	clientInfo.setRoomNo(0);
	clientInfo_list.push_back(clientInfo);
	for(ClientInfo ci :  clientInfo_list) {
		cout << ci.getId() << endl;
	}
}

void CreateLogin::findClientInfo()
{
	for(ClientInfo ci : clientInfo_list) {
		if(ci.getId() == id && ci.getPassword() == password) {
			cout << "Successfully logged in" << endl;
			//break;
		}
		cout << ci.getId() << endl;
	}
	cout << "Failed logging in" << endl;
	exit(4);
}

ClientInfo CreateLogin::getClientInfo()
{
	return clientInfo;
}

// void CreateLogin::setClientInfoList(list<ClientInfo> clientInfo_list)
// {
// 	this->clinetInfo_list = clientInfo_list;
// }

list<ClientInfo> CreateLogin::getClientInfoList()
{
	return clientInfo_list;
}	


// 
// 	switch(option) {
// 		case 1:
// 			cout << "ID: ";
// 			cin >> id;
// 			cout << "Password: ";
// 			cin >> password;
// 			// CreateLogin::createAccount(id, password);
// 			break;
// 		case 2:
// 			cout << "ID: ";
// 			cin >> id;
// 			cout << "Password: ";
// 			cin >> password;
// 			CreateLogin::login(id, password);
// 			cout << "You are successfully logged in" << endl;
// 			break;
// 		case 3:
// 			cout << "Exit" << endl;
// 			exit(0);
// 		default:
// 			CreateLogin::askClient(clientInfo_list);
// 	}
// 	return clientInfo;
// }
// 
// void CreateLogin::createAccount(string id, string password)
// {
// 	for(ClientInfo ci : clientInfo_list) {
// 		if(ci.getId() == id) {
// 			cout << "Same ID already exists" << endl;
// 			CreateLogin::askClient(clientInfo_list);
// 			break;
// 		}
// 	}
// 	clientInfo.setId(id);
// 	clientInfo.setPassword(password);
// 	cout << "Your account is successfully created" << endl;
// 
// }
// 
// void CreateLogin::login(string id, string password)
// {
// 	// Loop through clientList and find the same id and password
// 	// client = found_client
// 	// TODO: Get clientInfo_list from server
// 	for(ClientInfo ci : clientInfo_list) {
// 		if(ci.getId() == id && ci.getPassword() == password) {	
// 			cout << "You are successfully loggine in" << endl;
// 			clientInfo = ci;
// 			break;	
// 		} else if (ci.getId() == id && ci.getPassword() != password) {
// 			cout << "Your password is incorrect" << endl;
// 			CreateLogin::askClient(clientInfo_list);
// 			break;
// 		} 
// 	}
// 	cout << "Your account doesn't exist" << endl;
// 	CreateLogin::askClient(clientInfo_list);
// }
