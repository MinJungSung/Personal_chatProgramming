#include "server.h"

using namespace std;
using namespace boost::algorithm;
using std::cout;
using std::endl;
using std::cin;
using std::string;

namespace bst = boost;

void Server::send_to_all(int j, int i, int sockfd, int nbytes_recvd, char *recv_buf, fd_set *master)
{
	if (FD_ISSET(j, master)){
		if (j != sockfd && j != i) {
			if (send(j, recv_buf, nbytes_recvd, 0) == -1) {
				perror("send");
			}
		}
	}
}

void Server::send_recv(int i, fd_set *master, int sockfd, int fdmax)
{
	int nbytes_recvd, j;
	char recv_buf[BUFSIZE];

	// Connection failure
	if ((nbytes_recvd = recv(i, recv_buf, sizeof(recv_buf) - 1, 0)) <= 0) {
		if (nbytes_recvd == 0) {
			printf("socket %d hung up\n", i);
		}else {
			perror("recv");
		}
		close(i);
		FD_CLR(i, master);
	// Connection success
	} else if(nbytes_recvd > 1){ 	



/*

for(vector<vector<string>>::iterator it = room_list.begin(); it != room_list.end(); ++it) { 
    //obtain and iterate over the inner vector
    for(vector<string>::iterator it2 = *it.begin(); it2 != *it.end(); ++it2) {
        cout << *it2; //obtain and print our string
    }
}
*/

		string recv_buf_toString(recv_buf);
		trim(recv_buf_toString);
		// 1) ClientInformation
		if((recv_buf_toString.substr(0,18)).compare("clientInformation:") == 0){
			recv_buf_toString = recv_buf_toString.substr(18);
			clientInfoList->setClientInformation(recv_buf_toString, i);
			vector<string> temp = clientInfoList->getClientInformation(i);
			string s = "";
			for_each(temp.begin(), temp.end(),[&](const string &piece){s+=piece;});
			cout << s << endl;
			//vector<string> clientInformation;	
			//cout << "clientInformation" << endl;
			//while(!recv_buf_toString.empty()){
			//	if (recv_buf_toString.find_first_of(",") != string::npos) {
			//		clientInformation.push_back(recv_buf_toString.substr(0,recv_buf_toString.find_first_of(",")));
			//		recv_buf_toString = recv_buf_toString.substr(recv_buf_toString.find_first_of(",") + 1);
			//	} else {
			//		clientInformation.push_back(recv_buf_toString);
			//		clientInformation.push_back("0");
			//		clientInformation.push_back(to_string(i));
			//		recv_buf_toString = "";	
			//	}
			//}
			//string s = "";
			//for_each(clientInformation.begin(),clientInformation.end(),[&](const string &piece){s+=piece;});
			//clientInfo_list.push_back(clientInformation);
		
		// 2) CreateRoom
		/*
		} else if((recv_buf_toString.substr(0,10)).compare("createRoom") == 0) {



			for(vector<string> ci : clientInfo_list){
				if(stoi(ci[3]) == i){
					if(stoi(ci[2]) == 0) {
						//TODO:send error message
					} else {
						//TODO:goto rest of the code
					}
				}
			}


			int room = 0;
			// Skipped room
			for(map<int,int>::iterator it = room_list.begin(); it != room_list.end(); ++it){
				if(it->first == room){
					cout << "Increased Room" << endl;
					cout << room << endl;
					room++;
				}else{
					room_list.emplace(room,1);
					for(vector<string> ci : clientInfo_list){
						cout << "room " << ci[2] << endl;
						if(stoi(ci[3]) == i){
							// Decrease number for original room
							cout << "original room: " << ci[2] << endl;
							int originalRoom = stoi(ci[2]);
							((room_list.find(originalRoom))->second)--;
							ci[2] = to_string(room);
							cout << "moved to: " << ci[2] << endl;
							break;
						}
					}
					
				}
			}
			room_list.emplace(room,1);
			//TODO: ci = ClientInfoList.getClientInformation(i);
			for (int num = 0; num < clientInfo_list.size(); num++) {
				if (stoi(clientInfo_list[num][3]) == i) {
				 	string s="";
				 	for_each(clientInfo_list[num].begin(), clientInfo_list[num].end(),[&](const string &piece){s+=piece;});
				 	cout << s << endl;
					cout << "original room " << clientInfo_list[num][2] << endl;
					int originalRoom = stoi(clientInfo_list[num][2]);
					((room_list.find(originalRoom))->second)--;
					clientInfo_list[num][2] = to_string(room);
					string k="";
					for_each(clientInfo_list[num].begin(), clientInfo_list[num].end(),[&](const string &piece){k+=piece;});
					cout << k << endl;
					cout << "moved to " << clientInfo_list[num][2] << endl;
					break;
				}
			}

			for(vector<string> ci : clientInfo_list){
				string s1="";
				for_each(ci.begin(),ci.end(),[&](const string &piece){s1+=piece;});
				cout << "== end of createRoom ==" << s1 << endl;
			}

			string s = "You created room " + to_string(room) + "\n";
			char* sockfd_char = new char[s.length() + 1];
			strcpy(sockfd_char, s.c_str());
			send_to_all(i, i+1, sockfd, strlen(sockfd_char), sockfd_char, master);

		// 3) ExitRoom
		} else if((recv_buf_toString.substr(0,8)).compare("exitRoom") == 0){
			int room = 0;
			string leftUser = "";
			for(int num = 0; num < clientInfo_list.size(); num++){
				string s = "";
				for_each(clientInfo_list[num].begin(),clientInfo_list[num].end(),[&](const string &piece){s+=piece;});
				cout << s << endl;
				// Find who left room
				if(stoi(clientInfo_list[num][3]) == i){
					room = clientInfo_list[num][2];
					room_list.find(room)->second--;
					room_list.find(0)->second++; 
	
					leftUser = clientInfo_list[num][0];
					// Send messages
					cout << "currRoom " << room << endl;
					cout << "Exit room " << room_list.find(room)->second << endl;
					if((room_list.find(room)->second) == 0 && room != 0){
						printf("Room %d disappeared\n", room);
						room_list.erase(room);
					} else {
						// Message to others in chat
						string leftMessageToOthers = leftUser + " left this chat\n";
						char* sockfd_char_toOthers = new char[leftMessageToOthers.length() + 1];
						strcpy(sockfd_char_toOthers, leftMessageToOthers.c_str());

						for(int n = 0; n < clientInfo_list.size(); n++){
							if(stoi(clientInfo_list[num][2]) == room){
								send_to_all(stoi(clientInfo_list[num][3]), i, sockfd, strlen(sockfd_char_toOthers), sockfd_char_toOthers, master);
							}
						}
					}
					// Message to leftUser
					string leftMessage_toMyself = "You left the chat\n";
					char* sockfd_char_toMyself = new char[leftMessage_toMyself.length() + 1];
					strcpy(sockfd_char_toMyself, leftMessage_toMyself.c_str());
					send_to_all(i, i+1, sockfd, strlen(sockfd_char_toMyself), sockfd_char_toMyself, master);
					clientInfo_list[num][2] = "0";
					break;
				}
			}

		// 4) JoinRoom
		} else if((recv_buf_toString.substr(0,8)).compare("joinRoom") == 0){
			

		// 5) ShowRoom
		} else if((recv_buf_toString.substr(0,8)).compare("showRoom") == 0){
			for(map<int,int>::iterator it = room_list.begin(); it != room_list.end(); ++it){
				cout << "Room " << (*it).first << "->" << (*it).second << " users" << endl;
			}			

		// 6) Message
		} else {
			int room = 0;
			string senderUsername = "";
			for(int num = 0; num < clientInfo_list.size(); num++){
				// Find which socket sends the message
				if(stoi(clientInfo_list[num][3]) == i){
					// find room to send
					room = stoi(clientInfo_list[num][2]);
					senderUsername = clientInfo_list[num][0];
					break;
				}
			}
			senderUsername = senderUsername + ":";
			senderUsername = senderUsername.append(string(recv_buf, nbytes_recvd));	

			char* sockfd_char = new char[senderUsername.length() + 1];
			strcpy(sockfd_char, senderUsername.c_str());

			cout << "room:" << room << endl;
			for(vector<string> ci : clientInfo_list){
				if(stoi(ci[2]) == room){
					cout << "room check: " << ci[2] << endl;
					cout << "port check: " << ci[3] << endl;
				
					send_to_all(stoi(ci[3]), i, sockfd, strlen(sockfd_char), sockfd_char, master);
				}
			}
			*/
		}
	}	
}

void Server::connection_accept(fd_set *master, int *fdmax, int sockfd, struct sockaddr_in *client_addr)
{
	socklen_t addrlen;
	int newsockfd;
	
	addrlen = sizeof(struct sockaddr_in);
	if((newsockfd = accept(sockfd, (struct sockaddr *)client_addr, &addrlen)) == -1) {
		// TODO
		//for(vector<string> ci : clientInfo_list){

		//}
		perror("accept");
		exit(1);
	}else {
		FD_SET(newsockfd, master);
		if(newsockfd > *fdmax){
			*fdmax = newsockfd;
		}
		room_list.find(0)->second++;
		printf("new connection from %s on port %d \n",inet_ntoa(client_addr->sin_addr), ntohs(client_addr->sin_port));
	}
}
	
void Server::connect_request(int *sockfd, struct sockaddr_in *my_addr)
{
	int yes = 1;
		
	if ((*sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("Socket");
		exit(1);
	}
		
	my_addr->sin_family = AF_INET;
	my_addr->sin_port = htons(4950);
	my_addr->sin_addr.s_addr = INADDR_ANY;
	memset(my_addr->sin_zero, '\0', sizeof my_addr->sin_zero);
		
	if (setsockopt(*sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
		perror("setsockopt");
		exit(1);
	}
		
	if (bind(*sockfd, (struct sockaddr *)my_addr, sizeof(struct sockaddr)) == -1) {
		perror("Unable to bind");
		exit(1);
	}
	if (listen(*sockfd, 10) == -1) {
		perror("listen");
		exit(1);
	}
	printf("\nTCPServer Waiting for client on port 4950\n");
	fflush(stdout);
}

void Server::tcpListener(int sockfd, int fdmax, int i, struct sockaddr_in my_addr, struct sockaddr_in client_addr, fd_set master, fd_set read_fds)
{
	FD_ZERO(&master);
	FD_ZERO(&read_fds);
	connect_request(&sockfd, &my_addr);
	FD_SET(sockfd, &master);
	fdmax = sockfd;
	while(1){
		read_fds = master;
		if(select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1){
			perror("select");
			exit(4);
		}
		for (i = 0; i <= fdmax; i++){
			if (FD_ISSET(i, &read_fds)){
				if (i == sockfd){
					connection_accept(&master, &fdmax, sockfd, &client_addr);
				} else{
					send_recv(i, &master, sockfd, fdmax);
				}
			}
		}
	}
}

int main(int argc, char* argv[])
{

	fd_set master;
	fd_set read_fds;
	int fdmax, i;
	int sockfd = 0;
	struct sockaddr_in my_addr, client_addr;

	Server server;
	server.tcpListener(sockfd, fdmax, i, my_addr, client_addr, master, read_fds);
	return 0;
}

