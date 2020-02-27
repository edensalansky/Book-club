//
// Created by maiy@wincs.cs.bgu.ac.il on 08/01/2020.
//
#include "../../include/message.h"
#include <unordered_map>
#include <vector>
#include "../../include/book.h"
#include "../../include/client.h"
#include <iostream>

using namespace std;

Send::Send(string msg, int subscriptionId, string command, client &client) : message(msg), subscriptionID(),
                                                                             destination(), command(command), bookName(),
                                                                             Client(&client) {
    this->destination = msg.substr(0, msg.find(" "));
    if (command != "status") {
        msg = msg.substr(msg.find(" ")+1);
        this->bookName = msg;
    }
    this->subscriptionID = to_string(subscriptionId);
    setMessage(createMessage());
}

Send::~Send() {

}

Send &Send::operator=(Send &other) {
    if(&other==this)
        return *this;
    return copy(other);
}

Send::Send(Send &other) :message(other.getMessage()), subscriptionID(),
                         destination(), command(), bookName(),
                         Client() {
    copy(other);

}

Send &Send::copy(Send &other) {
    setMessage(other.getMessage());
    Client =other.Client;
    destination =other.destination;
    subscriptionID =other.subscriptionID;
    command =other.command;
    bookName =other.bookName;
    return *this;
}

string Send::createMessage() {
    string str = "";
    str = str + "SEND\n" +
          "destination:" + destination + "\n"+"\n";
    if (command == "add") {
        str = str + Client->getName() +
              " has added the book " + bookName ;
        Client->addBook(destination, bookName, false, "", true);
    } else if (command == "borrow") {
        str = str + Client->getName() +
              " wish to borrow " + bookName ;

    } else if (command == "return") {
        string lendername;
        unordered_map<string, vector<book *>>::const_iterator it = Client->getBookMap().find(destination);
        if (it != Client->getBookMap().end()) {
            for (book *item : it->second) {
                if (item->getName() .compare( bookName)==0)
                    lendername = item->getLenderName();
            }
        }
        Client->removeBook(destination, bookName);
        str = str + "Returning " + bookName + " to " + lendername ;

    } else if (command == "status") {
        str = str +"book status";
    }
    return str;

}

string Send::getDestination(){
    return destination;
}
