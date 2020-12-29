#include <string>
#include <string.h>
#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>

#include <unistd.h>
#include <netdb.h>
#include <cstdint>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "clientInfo.h"
#include "messageList.h"

class MessageHandler : public MessageList{

public:
	void sendTo(fd_set* master, int sender, vector<int> receiver, int messageChoice, string param);

};
