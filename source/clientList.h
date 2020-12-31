#include <string>
#include <string.h>
#include <iostream>
#include <map>
#include "messageHandler.h"

using namespace std;

class ClientList {
public:
	ClientList(fd_set master);
	
	bool create(int sender, string ci);
	bool connect(int sender, string ci);
	bool disconnect(int sender);
	bool changeClient(int sender, int index, string change);
	string getClientInfo(int sender, int index);
	vector<int> sendTo(int sender);
	string showClient();

private:
	map<int,ClientInfo> client_list;
	MessageHandler messageHandler;
	fd_set master;
};
