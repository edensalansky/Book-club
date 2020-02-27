CFLAGS:=-c -Wall -Weffc++ -g -std=c++11 -Iinclude
LDFLAGS:=-lboost_system  -lstdc++ -pthread



all: StompBookClubClient


StompBookClubClient: bin/book.o bin/KeyboardTask.o bin/SocketTask.o  bin/connected.o bin/disconnect.o bin/subscribe.o bin/unsubscribe.o bin/ID.o bin/connectionHandler.o bin/client.o bin/message.o bin/Send.o bin/status.o bin/main.o 

	@echo 'Building target: StompBookClubClient'
	@echo 'Invoking: C++ Linker'
	$(CC) -o bin/StompBookClubClient bin/book.o bin/KeyboardTask.o bin/SocketTask.o  bin/connected.o bin/disconnect.o bin/subscribe.o bin/unsubscribe.o bin/ID.o bin/connectionHandler.o bin/client.o bin/message.o bin/Send.o bin/status.o bin/main.o $(LDFLAGS) 
	@echo 'Finished building target: StompBookClubClient'
	@echo ' '

	

bin/main.o: main.cpp
	g++ $(CFLAGS) -o bin/main.o main.cpp

bin/connectionHandler.o: src/connectionHandler.cpp
	g++ $(CFLAGS) -o bin/connectionHandler.o src/connectionHandler.cpp

bin/book.o: src/book.cpp
	g++ $(CFLAGS) -o bin/book.o src/book.cpp

bin/client.o: src/client.cpp
	g++ $(CFLAGS) -o bin/client.o src/client.cpp
	
bin/KeyboardTask.o : src/KeyboardTask.cpp
	g++ $(CFLAGS)  -o bin/KeyboardTask.o src/KeyboardTask.cpp 

bin/SocketTask.o: src/SocketTask.cpp
	g++ $(CFLAGS) -o bin/SocketTask.o src/SocketTask.cpp
bin/connected.o: src/messages/connected.cpp
	g++ $(CFLAGS) -o bin/connected.o src/messages/connected.cpp

bin/disconnect.o: src/messages/disconnect.cpp
	g++ $(CFLAGS) -o bin/disconnect.o src/messages/disconnect.cpp

bin/subscribe.o: src/messages/subscribe.cpp
	g++ $(CFLAGS) -o bin/subscribe.o src/messages/subscribe.cpp

bin/unsubscribe.o: src/messages/unsubscribe.cpp
	g++ $(CFLAGS) -o bin/unsubscribe.o src/messages/unsubscribe.cpp

bin/ID.o: src/messages/ID.cpp
	g++ $(CFLAGS) -o bin/ID.o src/messages/ID.cpp
	
bin/message.o: src/messages/message.cpp
	g++ $(CFLAGS) -o bin/message.o src/messages/message.cpp

bin/Send.o: src/messages/Send.cpp
	g++ $(CFLAGS) -o bin/Send.o src/messages/Send.cpp
	
bin/status.o: src/messages/status.cpp
	g++ $(CFLAGS) -o bin/status.o src/messages/status.cpp

	
.PHONY: clean
clean:
	rm -f bin/*
