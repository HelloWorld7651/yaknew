CC=g++
CFLAGS= -g -std=c++17 -Wall 
INCLUDES= -I../dragonfly/include -I/usr/local/include -I/opt/homebrew/include
LDFLAGS= -L../dragonfly/lib -ldragonfly -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

COMMON= EventNetwork.cpp NetworkManager.cpp Sentry.cpp 

CLIENT_SRC= client.cpp Input.cpp NameEntry.cpp yakclient.cpp $(COMMON)
CLIENT_OBJ= $(CLIENT_SRC:.cpp=.o)

SERVER_SRC= server.cpp yakserver.cpp $(COMMON)
SERVER_OBJ= $(SERVER_SRC:.cpp=.o)

all: client server

client: $(CLIENT_OBJ)
	$(CC) $(CLIENT_OBJ) -o client $(LDFLAGS)

server: $(SERVER_OBJ)
	$(CC) $(SERVER_OBJ) -o server $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f *.o client server dragonfly.log