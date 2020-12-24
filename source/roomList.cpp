#include "roomList.h"

using namespace std;

int createRoom(){
	int room = 1;
	map<int,int>::iterator it;
	for(it = room_list.begin(); it != client_list.end(); ++it){
		if(it->first == room){
			room++;
		} else {
			room_list.emplace(room,1);
			break;
		}
	}
	if(it == client_list.end()){
		room_list.emplace(room,1);
	}
	return room;
}

void removeRoom(int roomNum){
	room_list.erase(roomNum);
}

void increaseNum(int roomNum){
	room_list.find(roomNum)->second++;
}

void decreaseNum(int roomNum){
	room_list.find(roomNum)->second--;
	if(room_list.find(roomNum)->second == 0){
		removeRoom(roomNum);
	}
}

bool findRoom(int roomNum){
	for(map<int,int>::iterator it = room_list.begin(); it != room_list.end(); ++it){
		if(it->first == roomNum){
			return true;
		}
	}
	return false;
}

int findNum(int roomNum){
	for(map<int,int>::iterator it = room_list.begin(); it != room_list.end(); ++it){
		if(it->first == roomNum){
			return it->second;	
		}
	}
	return -1;
}

string showRoom(){
	string roomString = "";
	for(map<int,int>::iterator it = room_list.begin(); it != room_list.end(); ++it){
		roomString = "Room " + (*it).first + " -> " + (*it).second + " users\n";
	}	
	return roomString;
}
