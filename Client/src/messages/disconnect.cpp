#include "../../include/message.h"
#include "../../include/client.h"

disconnect::disconnect(string msg, int receiptId ,client &client) : message(msg) ,Client(&client),receiptId() {
    this->receiptId = to_string(receiptId);

    setMessage(createMessage());
}

disconnect::~disconnect() {

}

disconnect::disconnect(disconnect &other) :message(other.getMessage()) ,Client() ,receiptId() {
copy(other);
}

disconnect &disconnect::operator=(disconnect &other) {
    if(&other==this)
        return *this;
    return copy(other);
}

disconnect &disconnect::copy(disconnect &other) {
    setMessage(other.getMessage());
    Client =other.Client;
    receiptId =other.receiptId;
    return *this;
}

string disconnect::createMessage() {
    string str="";
    str =str+"DISCONNECT\n"+
         "receipt:" + receiptId ;
    return str;

}

//
// Created by maiy@wincs.cs.bgu.ac.il on 08/01/2020.
//

