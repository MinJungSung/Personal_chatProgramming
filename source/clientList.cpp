#include "clientList.h"

using namespace std;

ClientList::ClientList(fd_set master){
	this->master = master;
}

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
		if(it->second.getUsername().compare(information[0]) == 0){
			messageHandler.sendTo(&master, sender, {sender}, 9, "");
			return false;
		}
	}
	ClientInfo clientInfo(information);
	client_list.emplace(sender, clientInfo);
	return true;
}

bool ClientList::connect(int sender, string ci){
	vector<string> information;
	while(!ci.empty()){
		if(ci.find_first_of(",") != string::npos){
			information.push_back(ci.substr(0,ci.find_first_of(",")));
			ci = ci.substr(ci.find_first_of(",") + 1);
		} else {
			information.push_back(ci);
			ci = "";
		}
	}
	map<int,ClientInfo>::iterator it;
	for(it = client_list.begin(); it != client_list.end(); ++it){
		if(it->second.getUsername().compare(information[0])){
			if(it->second.getPassword().compare(information[1])){
				messageHandler.sendTo(&master, sender, {sender}, 11, "");

				auto const value = move(it->second);
				client_list.erase(it->first);
				client_list.insert({sender, move(value)});

				return true;
			}
		} 			
	}
	if(it == client_list.end()){
		messageHandler.sendTo(&master, sender, {sender}, 12, "");
		return false;
	}			
	return false;
}

bool ClientList::disconnect(int sender){
	map<int,ClientInfo>::iterator it;
	for(it = client_list.begin(); it != client_list.end(); ++it){
		if(it->first == sender){
			it->second.setSockfd(-1);
			it->second.setRoomNumber(-1);

			auto const value = move(it->second);
			client_list.erase(sender);
			client_list.insert({-1, move(value)});

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
					messageHandler.sendTo(&master, sender, {sender}, 13, "Username");
					return true;
				//Password
				case 1:
					it->second.setPassword(change);
					messageHandler.sendTo(&master, sender, {sender}, 13, "Password");
					return true;
				//RoomNumber
				case 2:
					it->second.setRoomNumber(stoi(change));
					messageHandler.sendTo(&master, sender, {sender}, 13, "RoomNumber");
					return true;
				//Sockfd
				case 3:
					{
					it->second.setSockfd(stoi(change));
					auto const value = move(it->second);
					client_list.erase(sender);
					client_list.insert({stoi(change), move(value)});
					messageHandler.sendTo(&master, sender, {sender}, 13, "Sockfd");
					return true;
					}
				//default
				default:
					messageHandler.sendTo(&master, sender, {sender}, 14, "");
					return false;
			}
		}
	}
}

string ClientList::getClientInfo(int sender, int index){
	string result = "";
	map<int,ClientInfo>::iterator it;
	for(it = client_list.begin(); it != client_list.end(); ++it){
		if(it->first == sender){
			switch(index){
				case 0:
					result += it->second.getUsername();
					break;
				case 1:
					result += it->second.getPassword();
					break;	
				case 2:
					result += it->second.getRoomNumber();
					break;
				case 3:
					result += it->second.getSockfd();
					break;
				default:
					messageHandler.sendTo(&master, sender, {sender}, 14, "");
					break;
			}
		}
	}
	return result;
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

string ClientList::showClient(){
	string clientString = "";
	for(map<int,ClientInfo>::iterator it = client_list.begin(); it != client_list.end(); ++it){
		clientString += "Socket " + to_string(it->first) + " Username: " +  it->second.getUsername() + "\n";
	}
	return clientString;
}
