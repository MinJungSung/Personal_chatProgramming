#include <string.h>
#include <string>
#include <iostream>
#include <vector>

#define SENDER 3

using namespace std;

class ClientInfoList{
	public:
		void setClientInformation(string s, int sockfd);
		vector<string> getClientInformation(int sockfd);
		void changeClientInformation(int sockfd, int index, string change);
		vector<string> getChangedClientInformation(int sockfd, int index, string change);
	private: 
		vector<vector<string>> clientInfo_list;			//clientInfo_list<username, password, roomNumber, sockfd>

};
