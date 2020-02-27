//
// Created by maiy@wincs.cs.bgu.ac.il on 08/01/2020.
//

#include "../include/SocketTask.h"
#include "../include/connectionHandler.h"
#include "../include/message.h"


SocketTask::SocketTask(client &Client, ConnectionHandler &connectionHandler) : Client(&Client), connectionHandler(&connectionHandler){}

void SocketTask::runSocketTask() {

    while (Client->isConnectedSocket()) {
        string answer;
        if (connectionHandler->getLine(answer)) {
            string command = answer.substr(0, answer.find("\n"));
            cout << answer << endl;
            if (command == "MESSAGE") {
                processSend(answer);
            }
            else if (command == "RECEIPT") {
                if (!Client->isConnectedKeyBoard()) {
                    answer = answer.substr(answer.find('\n'));
                    answer = answer.substr(answer.find(':') + 1);
                    string receiptID = answer.substr(0, answer.find("\n"));
                    if (receiptID == Client->getdisconnectID()) {
                        connectionHandler->close();
                        Client->disconnectSocket();
                    }
                }
            }
            else if(command=="ERROR"){
                cout<<"Login failed. Please enter 'bye'" << endl;
                Client->disconnectSocket();
            }
        }
    }

}

void SocketTask::processSend(string answer) {
    answer = answer.substr(answer.find(':') + 1);
    string subscriptionID = answer.substr(0, answer.find('\n'));
    answer = answer.substr(answer.find(':') + 1);
    string messageID = answer.substr(0, answer.find("\n"));
    answer = answer.substr(answer.find(':') + 1);
    string destination = answer.substr(0, answer.find("\n\n"));
    answer = answer.substr(answer.find("\n")+1);
    answer = answer.substr(answer.find("\n")+1);
    //answer = answer.substr(answer.find("\n")+1);
    string msgBody = answer;
    if(answer.find("\n")!=string::npos)
        msgBody = answer.substr(0,answer.find("\n"));
    if (msgBody.find("Returning") != string::npos) {
        string name = msgBody.substr(msgBody.find("to") + 3);
        if (Client->getName() .compare( name)==0) {
            string bookName = msgBody.substr(msgBody.find(" ") + 1);
            bookName = bookName.substr(0, bookName.find("to")-1);
            Client->returnBook(bookName, destination);
        }
    }
    else if (msgBody.find("status") != string::npos) {
        status *bookstatus = new status(msgBody, destination, subscriptionID, *Client);
        string msg = bookstatus->getMessage();
        connectionHandler->sendLine(msg);
        delete(bookstatus);
    }
    else if (msgBody.find("borrow")!=string::npos) {
        if (msgBody.substr(0, msgBody.find(" ")) != Client->getName()) {
            string bookName = msgBody.substr(msgBody.find("borrow") + 7);
            if(bookName.find("\n")!=string::npos)
                bookName=bookName.substr(0,bookName.find("\n"));
            if (Client->checkLibrary(destination, bookName)) {
                string hasBook = "";
                hasBook = hasBook + "SEND\n" +
                          "destination:" + destination + "\n" + "subscription-id:" + subscriptionID + "\n\n" +
                          Client->getName() + " has " + bookName;
                connectionHandler->sendLine(hasBook);
            }
        }
    }
    else if(msgBody.find("added")!=string::npos){

    }
    else if (msgBody.find("has")!=string::npos) {
        string lenderName = msgBody.substr(0, msgBody.find(" "));
        string bookName = msgBody.substr(msgBody.find("has") + 4);
        if(bookName.find("\n")!=string::npos)
            bookName=bookName.substr(0,bookName.find("\n"));
        if (lenderName .compare( Client->getName())!=0) {
            if (Client->checkWishlist(destination, bookName)) {
                Client->removeFromWishlist(bookName, destination);
                Client->addBook(destination, bookName, true, lenderName, true);
                string takeBook = "";
                takeBook = takeBook + "SEND\n" +
                           "destination:" + destination + "\n" + "subscription-id:" + subscriptionID + "\n\n" +
                           "Taking " +
                           bookName + " from " + lenderName;
                connectionHandler->sendLine(takeBook);
            }
        }}else if (msgBody.find("Taking") != string::npos) {
                string lenderName = msgBody.substr(msgBody.find("from") + 5);
               if(lenderName.find("\n")!=string::npos)
                      lenderName=lenderName.substr(0,lenderName.find("\n"));
                string bookName = msgBody.substr(msgBody.find("Taking") + 7);
                bookName = bookName.substr(0, bookName.find("from") - 1);
                if (lenderName .compare( Client->getName())==0) {
                    Client->removeBook(destination, bookName);
                }
            }
        }


