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
#include <vector>

using namespace std;

int main() {

vector<vector<string>> vs;
vs.push_back({ "xyzzy", "plugh", "abracadabra" }); 
vs.push_back({ "xyzzy", "plugh", "abracadabra" });
vs.push_back({ "xyzzy", "plugh", "abracadabra" });


for(auto it = vs.begin(); it != vs.end(); it++){
	cout << (*it)[0] << endl;

}


return 0;
}

