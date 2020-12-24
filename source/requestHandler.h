#include <string>
#include <string.h>
#include <iostream>
#include "clientList.h"
#include "roomList.h"

#define BUFSIZE 1024
#define LOUNGE 0

#define USERNAME 0
#define PASSWORD 1
#define ROOMNUMBER 2
#define SOCKFD 3

using namespace std;

class RequestHandler {
public:
	RequestHandler(int sockfd, fd_set* master);

	void requestDispatcher(int sender, string request);
	void clientInformation(int sender, string request);
	void createRoom(int sender);
	void exitRoom(int sender);
	void joinRoom(int sender);
	void showRoom(int sender);
	void message(int sender);

	void connectionHandler(int sender, string request);
	void connected(int sender); 
	void disconnected(int sender);

private:
	string request;
	int sender, sockfd;
	fd_set* master;

	ClientList clientList;
	RoomList roomList;
	MessageHandler messageHandler;
};
