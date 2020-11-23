#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <pthread.h>
#include <cstdint>
#include <iostream>


void PrintPointers(char *value)
{
	printf("%s", value);
}

int main() {

char* prt1 = "memory";
char* prt2 = "issue";

int new_size = sizeof(prt1) + sizeof(prt2) + 1;

char* newBuffer = (char *)malloc(new_size);
strcpy(newBuffer,prt1);
strcat(newBuffer,prt2);

//printf("%s", newBuffer);

PrintPointers(newBuffer);

return 0;
}

