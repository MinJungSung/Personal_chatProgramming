#include <vector>
#include <string>
#include <string.h>
#include <iostream>


#define USERNAME 0
#define PASSWORD 1
#define ROOMNUMBER 2
#define SOCKFD 3

/*
typedef enum {
	USERNAME = 0,
	PASSWORD = 1,
	ROOMNUMBER = 2,
	SOCKFD = 3
}index;
*/
using namespace std;

class ClientInfo {

public:
	//Constructor
	//ClientInfo();
	ClientInfo(vector<string> clientInformation);
	//~ClientInfo();
	

	//Function
	void setUsername(string username);
	string getUsername()const;

	void setPassword(string password);
	string getPassword()const;

	void setRoomNumber(int roomNumber);
	int getRoomNumber()const;

	void setSockfd(int sockfd);
	int getSockfd()const;

private:
	string username;
	string password;
	int roomNumber;
	int sockfd;	
};
