//
// Created by maiy@wincs.cs.bgu.ac.il on 11/01/2020.
//

#include "../../include/message.h"

status::status(string msg, string destination, string subscriptionId, client &client): message(msg), destination(destination), inventory(), subscriptionId(subscriptionId), Client(&client){
    inventory = Client->printInventory(destination);
    setMessage(createMessage());
}

status::~status() {

}

status &status::operator=(status &other) {
    if(&other==this)
        return *this;
    return copy(other);
}

status::status(status &other): message(other.getMessage()), destination(), inventory(), subscriptionId(), Client(){
    copy(other);
}

status &status::copy(status &other) {
    setMessage(other.getMessage());
    destination =other.destination;
    Client =other.Client;
    subscriptionId =other.subscriptionId;
    inventory =other.inventory;
    return *this;
}

string status::createMessage() {
    string str = "";
    str = str + "SEND\n" +
          "destination:" + destination + "\n" + "subscription-id:" + subscriptionId + "\n\n" + inventory;
    return str;
}
