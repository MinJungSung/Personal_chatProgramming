#include <string>
#include <string.h>
#include <iostream>
#include <map>

using namespace std;

class RoomList {
public:
	RoomList();
	
	int createRoom();
	void removeRoom(int roomNum);
	void increaseNum(int roomNum);
	void decreaseNum(int roomNum);
	bool findRoom(int roomNum);
	int findNum(int roomNum);
	string showRoom();

private:
	map<int,int> room_list = {{0,0}};
};
