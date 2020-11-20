#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>

#define MAX 80
#define PORT 8080
#define SA struct sockaddr

// Function designed for chat between client and server
void func(int sockfd)
{
	char buff[MAX];
	int n;

	// infinite loop for chat
	for (;;) {
		// bzero(void *s, size_t n) 
		// The bzero() function shall place n zero-valued bytes in the area pointed to by s
		bzero(buff, MAX);

		// read the message from client and copy it in buffer
		read(sockfd, buff, sizeof(buff));
		// print buffer which contains the client contents
		printf("From client: %s\t To client : ", buff);
		bzero(buff, MAX);
		n = 0;

		// copy server message in the buffer
		while ((buff[n++] = getchar()) != '\n');

		// and send that buffer to client
		write(sockfd, buff, sizeof(buff));

		// if msg contains "Exit" then server exit and chat ends
		if (strncmp("exit", buff, 4) == 0) {
			printf("Server Exit...\n");
			break;
		}
	}
}

// Driver function
int main () 
{
	int sockfd, connfd, len;
	struct sockaddr_in, servaddr, cli;

	// socket create and verification
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

}
