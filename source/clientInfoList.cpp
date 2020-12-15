#include "clientInfoList.h"

	
// Setter
void ClientInfoList::setClientInformation(string s, int sockfd){	
	vector<string> clientInformation;
	while(!s.empty()){
		if(s.find_first_of(",") != string::npos) {
			clientInformation.push_back(s.substr(0, s.find_first_of(",")));
			s = s.substr(s.find_first_of(",") + 1);
		} else {
			clientInformation.push_back(s);
			clientInformation.push_back("0");
			clientInformation.push_back(to_string(sockfd));
			s = "";
		}
	}
}

// Getter
vector<string> ClientInfoList::getClientInformation(int sockfd){
	for(auto it = clientInfo_list.begin(); it != clientInfo_list.end(); it++){
		if(stoi((*it)[SENDER]) == sockfd){
			return *it;
		}
	}
}

// Change clientInformation
void ClientInfoList::changeClientInformation(int sockfd, int index, string change){
	for(auto it = clientInfo_list.begin(); it != clientInfo_list.end(); it++){
		if(stoi((*it)[SENDER]) == sockfd){
			(*it)[index] = change;
		}
	}
}

// Getter of changedClientInformation
vector<string> ClientInfoList::getChangedClientInformation(int sockfd, int index, string change){
	for(auto it = clientInfo_list.begin(); it != clientInfo_list.end(); it++){
		if(stoi((*it)[SENDER]) == sockfd){
			(*it)[index] = change;
			return *it;
		}
	}
}

