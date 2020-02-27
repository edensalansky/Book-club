//
// Created by maiy@wincs.cs.bgu.ac.il on 08/01/2020.
//

#ifndef CLIENT_SOCKETTASK_H
#define CLIENT_SOCKETTASK_H


#include "connectionHandler.h"
#include "client.h"

class SocketTask {
public:
    SocketTask(client &Client, ConnectionHandler &connectionHandler);
    void runSocketTask();
    void processSend(string ans);
private:
    client* Client;
    ConnectionHandler* connectionHandler;
};


#endif //CLIENT_SOCKETTASK_H
