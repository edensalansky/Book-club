
#include "connectionHandler.h"
#include "client.h"
#include "message.h"
#include "KeyboardTask.h"
#include "SocketTask.h"
#include <thread>
#include <mutex>
#include <queue>


/**
* This code assumes that the server replies the exact text the client sent it (as opposed to the practical session example)
*/


int main(int argc, char **argv) {


        string input;
        getline(cin, input);
        string command = input.substr(0, input.find(" "));
        if (command == "login") {
            string message = input.substr(input.find(" ") + 1);
            input = input.substr(input.find(" ") + 1);
            string host = input.substr(0, input.find(':'));
            input = input.substr(input.find(':') + 1);
            short port = stoi(input.substr(0, input.find(" ")));
            mutex __mutex;
            ConnectionHandler *connectionHandler = new ConnectionHandler(host, port,__mutex);
            if (connectionHandler->connect()) {
                mutex _mutex;
                client *Client = new client(_mutex);
                connected *login = new connected(message, *Client);
                SocketTask sockettask = SocketTask(*Client, *connectionHandler);
                thread thread2(&SocketTask::runSocketTask, &sockettask);
                string msg = login->getMessage();
                connectionHandler->sendLine(msg);
                delete (login);
                KeyboardTask keyboardtask = KeyboardTask(*Client, *connectionHandler);
                thread thread1(&KeyboardTask::runKeyboardTask, &keyboardtask);
                thread1.join();
                thread2.join();
                delete(Client);
            } else {
                std::cerr << "Cannot connect to " << host << ":" << port << std::endl;
            }
            delete(connectionHandler);
        }

    return 0;
}


