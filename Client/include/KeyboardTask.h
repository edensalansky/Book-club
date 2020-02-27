//
// Created by maiy@wincs.cs.bgu.ac.il on 08/01/2020.
//

#ifndef CLIENT_KEYBOARDTASK_H
#define CLIENT_KEYBOARDTASK_H


#include "connectionHandler.h"
#include "client.h"

class KeyboardTask {
private:
    client* Client;
    ConnectionHandler* connectionHandler;
public:
    KeyboardTask(client &Client, ConnectionHandler &connectionHandler);
    void runKeyboardTask();
};


#endif //CLIENT_KEYBOARDTASK_H
