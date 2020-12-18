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

		for(map<int,ClientInfo>::iterator it = client_list.begin(); it != client_list.end(); ++it){
			if(it->second.getSockfd() == i){
				//Decrease roomNum count
				((room_list.find(it->second.getRoomNumber()))->second)--;
				//Remove Room if 0	
				if((room_list.find(it->second.getRoomNumber())->second) == 0 && it->second.getRoomNumber() != 0){
					printf("Room %d disappeared\n", it->second.getRoomNumber());
					room_list.erase(it->second.getRoomNumber());
				} else {
					// Message to others in chat
					string leftMessageToOthers = it->second.getUsername() + " left this chat\n";
					char* sockfd_char_toOthers = new char[leftMessageToOthers.length() + 1];
					strcpy(sockfd_char_toOthers, leftMessageToOthers.c_str());
					for(map<int,ClientInfo>::iterator others = client_list.begin(); others != client_list.end(); ++others){
						if(others->second.getRoomNumber() == it->second.getRoomNumber()){
							send_to_all(others->second.getRoomNumber(), i, sockfd, strlen(sockfd_char_toOthers), sockfd_char_toOthers, master);
						}
					}
				}									
				it->second.setSockfd(-1);
				it->second.setRoomNumber(-1);	
				break;
			}
		}

		close(i);
		FD_CLR(i, master);
	// Connection success
	} else if(nbytes_recvd > 1){ 	

		string recv_buf_toString(recv_buf);
		trim(recv_buf_toString);

		// 1) ClientInformation
		if((recv_buf_toString.substr(0,18)).compare("clientInformation:") == 0){
			recv_buf_toString = recv_buf_toString.substr(18);
			//string s = "";
			//for_each(temp.begin(), temp.end(),[&](const string &piece){s+=piece;});
			//cout << s << endl;
			vector<string> clientInformation;	
			cout << "clientInformation" << endl;
			while(!recv_buf_toString.empty()){
				if (recv_buf_toString.find_first_of(",") != string::npos) {
					clientInformation.push_back(recv_buf_toString.substr(0,recv_buf_toString.find_first_of(",")));
					recv_buf_toString = recv_buf_toString.substr(recv_buf_toString.find_first_of(",") + 1);
				} else {
					clientInformation.push_back(recv_buf_toString);
					clientInformation.push_back("0");
					clientInformation.push_back(to_string(i));
					recv_buf_toString = "";	
				}
			}
			//TODO:Think of a way to avoid error or at least passing an null or error
			ClientInfo clientInfo(clientInformation);
			client_list.emplace(i, clientInfo);
			
			cout << "check2" << endl;
			for(map<int,ClientInfo>::iterator it = client_list.begin(); it != client_list.end(); ++it){
				cout << it->first << " " << it->second.getUsername() <<  "\n";
			}
			
		
		// 2) CreateRoom
		
		} else if((recv_buf_toString.substr(0,10)).compare("createRoom") == 0) {

			int room = 0;
			string message = "";

			// Skipped room
			for(map<int,int>::iterator it = room_list.begin(); it != room_list.end(); ++it){
				if(it->first == room){
					cout << "Increased Room" << endl;
					cout << room << endl;
					room++;
				} else {
					for(map<int,ClientInfo>::iterator it = client_list.begin(); it != client_list.end(); ++it){
						if(it->second.getSockfd() == i){
							if(it->second.getRoomNumber() != 0){
								message = "You cannot create a room because you are already in a room\n";
							} else {
								// Decrease number for original room
								cout << "original room: " << it->second.getRoomNumber() << endl;
								((room_list.find(it->second.getRoomNumber()))->second)--;
								it->second.setRoomNumber(room);
								cout << "moved to: " << it->second.getRoomNumber() << endl;
								room_list.emplace(room,1);
								message = "You successfully created a room\n";
							}
							char* sockfd_char = new char[message.length() + 1];
							strcpy(sockfd_char, message.c_str());
							send_to_all(i, i+1, sockfd, strlen(sockfd_char), sockfd_char, master);
							break;
						}
					}
				}
			}

			// Create room at end
			for(map<int,ClientInfo>::iterator it = client_list.begin(); it != client_list.end(); ++it){
				if(it->second.getSockfd() == i){
					if(it->second.getRoomNumber() != 0){
						message = "You cannot create a room because you are already in a room\n";
					} else {
						// Decrease number for original room
						cout << "original room: " << it->second.getRoomNumber() << endl;
						((room_list.find(it->second.getRoomNumber()))->second)--;
						it->second.setRoomNumber(room);
						cout << "moved to: " << it->second.getRoomNumber() << endl;
						room_list.emplace(room,1);
						message = "You successfully created a room\n";
					}
					char* sockfd_char = new char[message.length() + 1];
					strcpy(sockfd_char, message.c_str());
					send_to_all(i, i+1, sockfd, strlen(sockfd_char), sockfd_char, master);
					break;
				}
			}

		// 3) ExitRoom
		} else if((recv_buf_toString.substr(0,8)).compare("exitRoom") == 0){
			
			string leftMessageToOthers = "";
			string leftMessageToMyself = "";

			for(map<int,ClientInfo>::iterator it = client_list.begin(); it != client_list.end(); ++it){
				// Find who left room
				if(it->second.getSockfd() == i){
					room_list.find(it->second.getRoomNumber())->second--;
					room_list.find(0)->second++; 

					// Send messages
					cout << "Current Room " << it->second.getRoomNumber() << endl;
					if((room_list.find(it->second.getRoomNumber())->second) == 0 && it->second.getRoomNumber() != 0){
						printf("Room %d disappeared\n", it->second.getRoomNumber());
						room_list.erase(it->second.getRoomNumber());
					} else {

						// Message to others in chat
						leftMessageToOthers = it->second.getUsername() + " left this chat\n";
						char* sockfd_char_toOthers = new char[leftMessageToOthers.length() + 1];
						strcpy(sockfd_char_toOthers, leftMessageToOthers.c_str());
						for(map<int,ClientInfo>::iterator others = client_list.begin(); others != client_list.end(); ++others){
							if(others->second.getRoomNumber() == it->second.getRoomNumber()){
								send_to_all(others->second.getRoomNumber(), i, sockfd, strlen(sockfd_char_toOthers), sockfd_char_toOthers, master);
							}
						}
					}

					// Message to leftUser
					leftMessageToMyself = "You left the chat\n";
					char* sockfd_char_toMyself = new char[leftMessageToMyself.length() + 1];
					strcpy(sockfd_char_toMyself, leftMessageToMyself.c_str());
					send_to_all(i, i+1, sockfd, strlen(sockfd_char_toMyself), sockfd_char_toMyself, master);
					it->second.setRoomNumber(0);
					break;
				}
			}

		// 4) JoinRoom
		} else if((recv_buf_toString.substr(0,8)).compare("joinRoom") == 0){

			//Ask room
			string message = "Which room do you want to join?\n";
			char* message_sockfd_char = new char[message.length() + 1];
			strcpy(message_sockfd_char, message.c_str());
			send_to_all(i, i+1, sockfd, strlen(message_sockfd_char), message_sockfd_char, master);
			
			//Receive answer
			int room_nbytes_recvd;
			char room_recv_buf[BUFSIZE];
			if((room_nbytes_recvd = recv(i, room_recv_buf, sizeof(room_recv_buf) - 1, 0)) <= 0){
				if(room_nbytes_recvd == 0){
					printf("socket %d hung up\n",i);
				} else {
					printf("recv");
				}

				for(map<int,ClientInfo>::iterator it = client_list.begin(); it != client_list.end(); ++it){
					if(it->second.getSockfd() == i){
						//Decrease roomNum count
						room_list.find(it->second.getRoomNumber())->second--;
						//Remove Room if 0	
						if((room_list.find(it->second.getRoomNumber())->second) == 0 && it->second.getRoomNumber() != 0){
							printf("Room %d disappeared\n", it->second.getRoomNumber());
							room_list.erase(it->second.getRoomNumber());
						} else {
							// Message to others in chat
							string leftMessageToOthers = it->second.getUsername() + " left this chat\n";
							char* sockfd_char_toOthers = new char[leftMessageToOthers.length() + 1];
							strcpy(sockfd_char_toOthers, leftMessageToOthers.c_str());
							for(map<int,ClientInfo>::iterator others = client_list.begin(); others != client_list.end(); ++others){
								if(others->second.getRoomNumber() == it->second.getRoomNumber()){
									send_to_all(others->second.getRoomNumber(), i, sockfd, strlen(sockfd_char_toOthers), sockfd_char_toOthers, master);
								}
							}
						}									
						it->second.setSockfd(-1);
						it->second.setRoomNumber(-1);	
						break;
					}
				}

				close(i);
				FD_CLR(i,master);
			} else if (room_nbytes_recvd > 1) {
				cout << "received" << endl;
				string room_recv_buf_toString(room_recv_buf);
				trim(room_recv_buf_toString);
				cout << "Join " << room_recv_buf_toString << endl;

				bool joinedRoom = false;
				string errorMessage = "";
							
				//Find room
				map<int,int>::iterator room_it = room_list.find(stoi(room_recv_buf_toString));
				if(room_it != room_list.end()){
					joinedRoom = true;
					for(map<int,ClientInfo>::iterator client_it = client_list.begin(); client_it != client_list.end(); ++client_it){
						if(client_it->second.getSockfd() == i){
							room_it->second++;
							room_list.find(client_it->second.getRoomNumber())->second--;

							//Remove Room if 0	
							if((room_list.find(client_it->second.getRoomNumber())->second) == 0 && client_it->second.getRoomNumber() != 0){
								printf("Room %d disappeared\n", client_it->second.getRoomNumber());
								room_list.erase(client_it->second.getRoomNumber());
							} else {
								// Message to others in chat
								string leftMessageToOthers = client_it->second.getUsername() + " left this chat\n";
								char* sockfd_char_toOthers = new char[leftMessageToOthers.length() + 1];
								strcpy(sockfd_char_toOthers, leftMessageToOthers.c_str());
								for(map<int,ClientInfo>::iterator others = client_list.begin(); others != client_list.end(); ++others){
									if(others->second.getRoomNumber() == client_it->second.getRoomNumber()){
										send_to_all(others->second.getRoomNumber(), i, sockfd, strlen(sockfd_char_toOthers), sockfd_char_toOthers, master);
									}
								}
							}	

							client_it->second.setRoomNumber(stoi(room_recv_buf_toString));
							break;
						}	
					}
				}	


				//Send result message
				if(joinedRoom){
					errorMessage = "You sucessfully joined room\n";
				} else {
					errorMessage = "Sorry, you put incorrect room number\n";
				}
				char* error_sockfd_char = new char[errorMessage.length() + 1];
				strcpy(error_sockfd_char, errorMessage.c_str());
				send_to_all(i, i+1, sockfd, strlen(error_sockfd_char), error_sockfd_char, master);

			}
		

		// 5) ShowRoom
		} else if((recv_buf_toString.substr(0,8)).compare("showRoom") == 0){
			for(map<int,int>::iterator it = room_list.begin(); it != room_list.end(); ++it){
				cout << "Room " << (*it).first << "->" << (*it).second << " users" << endl;
			}			

		// 6) Message
		} else {
			
			int room = 0;
			string senderUsername = "";

			for(map<int,ClientInfo>::iterator it = client_list.begin(); it != client_list.end(); ++it){
				// Find which socket sends the message
				if(it->second.getSockfd() == i){
					// find room to send
					room = it->second.getRoomNumber();
					senderUsername = it->second.getUsername();
					break;
				}
			}

			senderUsername = senderUsername + ":";
			senderUsername = senderUsername.append(string(recv_buf, nbytes_recvd));	

			char* sockfd_char = new char[senderUsername.length() + 1];
			strcpy(sockfd_char, senderUsername.c_str());

			cout << "room:" << room << endl;
			for(map<int,ClientInfo>::iterator it = client_list.begin(); it != client_list.end(); ++it){
				if(it->second.getRoomNumber() == room){
					cout << "room check: " << it->second.getRoomNumber() << endl;
					cout << "port check: " << it->second.getSockfd() << endl;
				
					send_to_all(it->second.getSockfd(), i, sockfd, strlen(sockfd_char), sockfd_char, master);
				}
			}
		}
	}	
}

void Server::connection_accept(fd_set *master, int *fdmax, int sockfd, struct sockaddr_in *client_addr)
{
	socklen_t addrlen;
	int newsockfd;
	
	addrlen = sizeof(struct sockaddr_in);
	if((newsockfd = accept(sockfd, (struct sockaddr *)client_addr, &addrlen)) == -1) {
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

