#include <string>
#include <string.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "clientList.h"
#include "roomList.h"

#include <boost/algorithm/string.hpp>

#define BUFSIZE 1024
#define LOUNGE 0

#define USERNAME 0
#define PASSWORD 1
#define ROOMNUMBER 2
#define SOCKFD 3

using namespace std;
using namespace boost::algorithm;

class RequestHandler {
public:
	RequestHandler();

	void setDefault(int sockfd, fd_set* master);

	void requestDispatcher(int sender, string request);

	void clientInformation(int sender, string request);
	void createRoom(int sender);
	void exitRoom(int sender);
	void joinRoom(int sender, string request);
	void showRoom(int sender);
	void connected(int sender); 
	void disconnected(int sender);
	void message(int sender, string request);

private:
	int sender, sockfd;
	fd_set master;

	ClientList clientList = ClientList(master);
	RoomList roomList;
	MessageHandler messageHandler;
};
