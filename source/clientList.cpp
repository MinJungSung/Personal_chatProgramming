#include "clientList.h"

using namespace std;

ClientList::ClientList(){}

//clientInformation: will come in
bool ClientList::create(int sender, string ci){
	vector<string> information;
	while(!ci.empty()){
		if(ci.find_first_of(",") != string::npos){
			information.push_back(ci.substr(0,ci.find_first_of(",")));
			ci = ci.substr(ci.find_first_of(",") + 1);
		} else {
			information.push_back(ci);
			information.push_back("0");
			information.push_back(to_string(sender));
			ci = "";
		}
	}
	map<int,ClientInfo>::iterator it;
	for(it = client_list.begin(); it != client_list.end(); ++it){
		if(it->second.getUsername().comparare(information[0]){
			messageHandler.sendToSender(sockfd, master, sender, "Same username already exists\n");
			return false;
		}
	}
	if(it == client_list.end()){
		ClientInfo clientInfo(information);
		client_list.emplace(sender, clientInfo);
	}
	return true;
}

//Username and password will come in as clientInformation
//information[0]=username;
//information[1]=password;
bool ClientList::connect(int sender, string ci){
	vector<string> information;
	while(!ci.empty()){
		if(ci.find_first_of(",") != string::npost){
			information.push_back(ci.substr(0,ci.find_first_of(",")));
			ci = ci.substr(ci.find_first_of(",") + 1);
		} else {
			information.push_back(ci);
			ci = "";
		}
	}
	map<int,ClientInfo>::iterator it;
	for(it = client_list.begin(); it != client_list.end(); ++it){
		if(it->second.getUsername().compare(information[0]){
			if(it->second.getPassword().compare(information[1]){
				messageHandler.sendToSender(sockfd, master, sender, "Successfully connected\n");
				it->first = sender;
				return true;
			}
		} 			
	}
	if(it == client_list.end()){
		messageHandler.sendToSender(sockfd, master, sender, "Connection failed\n");
		return false;
	}			
	return false;
}

bool ClientList::disconnect(int sender){
	map<int,ClientInfo>::iterator it;
	for(it = client_list.begin(); it != client_list.end(); ++it){
		if(it->first == sender){
			it->first = -1;
			it->second.setSockfd(-1);
			it->second.setRoomNumber(-1);
			return true;
		}	
	}	
	return false;
}

bool ClientList::changeClient(int sender, int index, string change){
	map<int,ClientInfo>::iterator it;
	for(it = client_list.begin(); it != client_list.end(); ++it){
		if(it->first == sender){
			switch(index){
				//Username
				case 0:
					it->second.setUsername(change);
					messageHandler.sendToSender(sockfd, master, sender, "Username changed\n");
					return true;
				//Password
				case 1:
					it->second.setPassword(change);
					messageHandler.sendToSender(sockfd, master, sender, "Password changed\n");
					return true;
				//RoomNumber
				case 2:
					it->second.setRoomNumber(stoi(change));
					messageHandler.sendToSender(sockfd, master, sender, "RoomNumber changed\n");
					return true;
				//Sockfd
				case 3:
					it->first = stoi(change);
					it->second.setSockfd(stoi(change));
					messageHandler.sendToSender(sockfd, master, sender, "Sockfd changed\n");
					return true;
				//default
				default:
					messageHandler.sendToSender(sockfd, master, sender, "Couldn't change clientInfo\n");
					return false;
			}
		}
	}
}

string ClientList::getClientInfo(int sender, int index){
	map<int,ClientInfo>::iterator it;
	for(it = client_list.begin(); it != client_list.end(); ++it){
		if(it->first == sender){
			switch(index){
				case 0:
					it->second.getUsername();
					break;
				case 1:
					it->second.getPassword();
					break;	
				case 2:
					it->second.getRoomNumber();
					break;
				case 3:
					it->second.getSockfd();
					break;
				default:
					messageHandler.sendToSender(sockfd, master, sender, "Couldn't get clientInfo\n");
					break;
			}
		}
	}
}

vector<int> ClientList::sendTo(int sender){
	vector<int> sendList;
	int roomNum = client_list.find(sender)->second.getRoomNumber();
	map<int,ClientInfo>::iterator it;
	for(it = client_list.begin(); it != client_list.end(); ++it){
		if(it->second.getRoomNumber() == roomNum){
			sendList.push_back(it->first);
		}
	}	
	return sendList;
}
