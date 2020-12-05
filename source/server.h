#ifndef SERVER_H
#define SERVER_H

#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <map>
#include <list>
#include "client.h"
//#include "clientInfo.h"

#define PORT 4950
#define BUFSIZE 1024
#define MAX_SOCK 1024

using namespace std;
class Server {
public:

	void send_to_all(int j, int i, int sockfd, int nbyte_recvd, char* recv_buf, fd_set* master);
	void send_recv(int i, fd_set* master, int sockfd, int fmax);
	void connection_accept(fd_set* master, int* fdmax, int sockfd, struct sockaddr_in* client_addr);
	void connect_request(int* sockfd, struct sockaddr_in* my_addr);
	void tcpListener(int sockfd, int fdmax, int i, struct sockaddr_in my_addr, struct sockaddr_in client_addr, fd_set master, fd_set read_fds);
	void enterLounge(int sockfd);
	void send_to_room(int j, int i, int sockfd, int nbyte_recvd, char* recv_buf, fd_set* master);
	//void insertClientInfo(ClientInfo clientInfo);


void insertClientInfo(ClientInfo clientInfo) {
    //int opt = client.getOption();
    int opt = 1;
    if(opt == 1){

        clientInfo_list.push_back(clientInfo);
        cout << "list size: " << clientInfo_list.size() << endl;
        //test
        for(ClientInfo ci :  clientInfo_list) {
            cout << "client id: " << ci.getId() << endl;
        }
    } else if(opt == 2){
        ClientInfo recv_clientInfo = clientInfo;
        for(ClientInfo ci : clientInfo_list) {
            if(ci.getId() == recv_clientInfo.getId() && ci.getPassword() == recv_clientInfo.getPassword()) {
                cout << "Login succeeded" << endl;
                break;
            }
        }
        cout << "Login failed" << endl;
    } else {
        cout << "Exit like you chose" << endl;
        exit(4);
    }

}


	// Create ClientInfo list
	// socketfd == portNo
	std::map<int, std::list<int>> roomClient;	//map<roomNo, portNo>
	std::map<int, ClientInfo> onlineClient;		//map<portNo, id an password>
	std::list<ClientInfo> clientInfo_list;		//list<allClient>

	fd_set master;
	fd_set read_fds;
	
	// i == sender
	// j == iterator
	// sockfd == openned socket
	// fdmax == highest socket number
	int fdmax, i, room;
	int sockfd = 0;
	struct sockaddr_in my_addr, client_addr;	
	
	//CreateLogin createLogin;
	
};

#endif
