#include <string>
#include <string.h>
#include <iostream>

using namespace std;

class MessageHandler {
public:
	void sendToSender(int sockfd, fd_set* master, int sender, string message);
	void sendToAll(int sockfd, fd_set* master, int sender, map<int,ClientInfo> receiver, string message);
	void sendToOthersInRoom(int sockfd, fd_set* master, int sender, vector<int> receiver, string message);
};
