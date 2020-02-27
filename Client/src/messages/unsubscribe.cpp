//
// Created by maiy@wincs.cs.bgu.ac.il on 11/01/2020.
//

#include "../../include/message.h"

unsubscribe::unsubscribe(string msg, int receiptId, int subscriptionId) : message(msg), receiptID(), subscriptionID(),
                                                                      destination() {
    this->destination = msg;
    this->receiptID = to_string(receiptId);
    this->subscriptionID = to_string(subscriptionId);
    setMessage(createMessage());
}

unsubscribe::~unsubscribe() {

}
unsubscribe& unsubscribe ::operator=( unsubscribe& other){
    if(&other==this)
        return *this;
    return copy(other);

}

unsubscribe::unsubscribe(unsubscribe &other):message(other.getMessage()), receiptID(), subscriptionID(),
destination() {
    copy(other);

}

unsubscribe &unsubscribe::copy(unsubscribe &other) {
    setMessage(other.getMessage());
    subscriptionID =other.subscriptionID;
    destination =other.destination;
    receiptID =other.receiptID;
    return *this;
}


string unsubscribe::createMessage() {
    string str = "";
    str = str + "UNSUBSCRIBE\n" +
          "destination:" + destination + "\n" +
          "id:" + subscriptionID + "\n"+
          "receipt:" + receiptID;
    return str;

}
string unsubscribe::getDestination(){
    return destination;
}