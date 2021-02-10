CCFLAGS = -std=c++11 -Wall -Wextra -pedantic -I./

SERVER_SRC = clientInfo.cpp clientList.cpp messageHandler.cpp messageList.cpp requestHandler.cpp roomList.cpp server.cpp
CLIENT_SRC = client.cpp

SERVER_OBJS = server.o clientInfo.o clientList.o messageHandler.o messageList.o requestHandler.o roomList.o
CLIENT_OBJS = client.o

%.o: %.cpp
	g++ -c -g ${CCFLAGS} -o $*.o $*.cpp

client: $(CLIENT_OBJS)
	g++ -o $@ $(CLIENT_OBJS) -v

server: $(SERVER_OBJS)
	g++ -o $@ $(SERVER_OBJS) -v

all: $(client) $(server)

clean:
	rm -fr *.o client server
