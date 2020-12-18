#include "clientInfo.h"

using namespace std;
/*
ClientInfo::ClientInfo(){

}
*/
ClientInfo::ClientInfo(vector<string> clientInformation){
	this->username = clientInformation[USERNAME];
	this->password = clientInformation[PASSWORD];
	this->roomNumber = stoi(clientInformation[ROOMNUMBER]);
	this->sockfd = stoi(clientInformation[SOCKFD]);

	std::cout << "ClientInfo is created" << std::endl;
}
/*
ClientInfo::~ClientInfo(){
	cout << "ClientInfo is deleted" << endl;
}
*/
void ClientInfo::setUsername(string username){
	this->username = username;
}

string ClientInfo::getUsername(){
	return username;
}

void ClientInfo::setPassword(string password){
	this->password = password;
}

string ClientInfo::getPassword(){
	return password;
}

void ClientInfo::setRoomNumber(int roomNumber){
	this->roomNumber = roomNumber;
}

int ClientInfo::getRoomNumber(){
	return roomNumber;
}

void ClientInfo::setSockfd(int sockfd){
	this->sockfd = sockfd;
}

int ClientInfo::getSockfd(){
	return sockfd;
}

