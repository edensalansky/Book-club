//
// Created by maiy@wincs.cs.bgu.ac.il on 08/01/2020.
//

#include "../include/KeyboardTask.h"
#include <stdlib.h>
#include "../include/connectionHandler.h"
#include "../include/client.h"
#include "../include/ID.h"
#include "../include/message.h"
#include <thread>
#include <mutex>
#include <queue>
#include <stdlib.h>
#include <SocketTask.h>


KeyboardTask::KeyboardTask(client &Client, ConnectionHandler &connectionHandler) : Client(&Client), connectionHandler(
        &connectionHandler) {}


void KeyboardTask::runKeyboardTask() {
    ID *id = new ID();

    while (Client->isConnectedKeyBoard()) {

        string input;
        getline(cin, input);
        string command = input.substr(0, input.find(" "));
        input = input.substr(input.find(" ") + 1);
        if (command == "bye") {
            Client->disconnectKeyBoard("");
            connectionHandler->close();
        }
//}
        else if (command == "join") {
            int ID = id->getSubscriptionID();
            subscribe *join = new subscribe(input, id->getReceiptId(), ID);
            string msg = join->getMessage();
            string topic = join->getDestination();
            Client->addToSubIdMap(topic, ID);
            connectionHandler->sendLine(msg);
            delete (join);

        } else if (command == "exit") {
            string topic = input.substr(0, input.find(" "));
            int ID = Client->getFromSubIdMap(topic);
            unsubscribe *exit = new unsubscribe(input, id->getReceiptId(), ID);
            string msg = exit->getMessage();
            Client->removeFromSubId(topic);
            connectionHandler->sendLine(msg);
            delete (exit);


        } else if (command == "add") {

            string topic = input.substr(0, input.find(" "));
            int ID = Client->getFromSubIdMap(topic);
            Send *add = new Send(input, ID, command, *Client);
            string msg = add->getMessage();
            connectionHandler->sendLine(msg);
            delete (add);

        } else if (command == "borrow") {
            string topic = input.substr(0, input.find(" "));
            string bookName =input.substr(input.find(" ")+1);
            int ID = Client->getFromSubIdMap(topic);
            Client->addToWishlist(bookName, topic);
            Send *borrow = new Send(input, ID, command, *Client);
            string msg = borrow->getMessage();
            connectionHandler->sendLine(msg);
            delete (borrow);
        }
        if (command == "return") {
            string topic = input.substr(0, input.find(" "));
            string bookName=input.substr(input.find(" ")+1);
            int ID = Client->getFromSubIdMap(topic);
            Client->removeBook(topic, bookName);
            Send *returnbook = new Send(input, ID, command, *Client);
            string msg = returnbook->getMessage();
            connectionHandler->sendLine(msg);
            delete (returnbook);
        } else if (command == "status") {
            string topic = input.substr(0, input.find(" "));
            int ID = Client->getFromSubIdMap(topic);
            if(ID!=-1) {
                Send *bookstatus = new Send(input, ID, command, *Client);
                string msg = bookstatus->getMessage();
                connectionHandler->sendLine(msg);
                delete (bookstatus);
            }

        } else if (command == "logout") {
            int iD = id->getReceiptId();
            disconnect *logout = new disconnect(input, iD, *Client);
            string msg = logout->getMessage();
            connectionHandler->sendLine(msg);
            Client->disconnectKeyBoard(to_string(iD));
            delete (logout);
        }


    }
    delete(id);
}



