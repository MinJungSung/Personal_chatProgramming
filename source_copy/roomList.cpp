#include "roomList.h"

using namespace std;

int RoomList::createRoom(){
	int room = 0;
	map<int,int>::iterator it;
	for(it = room_list.begin(); it != room_list.end(); ++it){
		if(it->first == room){
			room++;
		} else {
			room_list.emplace(room,1);
			break;
		}
	}
	if(it == room_list.end()){
		room_list.emplace(room,1);
	}
	return room;
}

void RoomList::removeRoom(int roomNum){
	room_list.erase(roomNum);
}

void RoomList::increaseNum(int roomNum){
	room_list.find(roomNum)->second++;
}

void RoomList::decreaseNum(int roomNum){
	room_list.find(roomNum)->second--;
	if(room_list.find(roomNum)->second == 0 && roomNum != 0){
		removeRoom(roomNum);
	}
}

bool RoomList::findRoom(int roomNum){
	for(map<int,int>::iterator it = room_list.begin(); it != room_list.end(); ++it){
		if(it->first == roomNum){
			return true;
		}
	}
	return false;
}

int RoomList::findNum(int roomNum){
	for(map<int,int>::iterator it = room_list.begin(); it != room_list.end(); ++it){
		if(it->first == roomNum){
			return it->second;	
		}
	}
	return -1;
}

string RoomList::showRoom(){
	string roomString = "";
	for(map<int,int>::iterator it = room_list.begin(); it != room_list.end(); ++it){
		roomString += to_string((*it).first) + "," + to_string((*it).second) + ";";
	}	
	return roomString;
}
