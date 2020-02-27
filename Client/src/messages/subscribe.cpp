//
// Created by maiy@wincs.cs.bgu.ac.il on 08/01/2020.
//

#include "../../include/message.h"

subscribe::subscribe(string msg, int receiptId, int subscriptionId) : message(msg), receiptID(), subscriptionID(),
                                                                      destination() {
    this->destination = msg;
    this->receiptID = to_string(receiptId);
    this->subscriptionID = to_string(subscriptionId);
    setMessage(createMessage());
}

subscribe::~subscribe() {

}

subscribe &subscribe::operator=(subscribe &other) {
    if(&other==this)
        return *this;
    return copy(other);
}

subscribe &subscribe::copy(subscribe &other) {
    setMessage(other.getMessage());
    destination =other.destination;
    subscriptionID =other.subscriptionID;
    receiptID =other.receiptID;
    return *this;
}

subscribe::subscribe(subscribe &other) :message(other.getMessage()), receiptID(), subscriptionID(),
destination() {
    copy(other);

}

string subscribe::createMessage() {
    string str = "";
    str = str + "SUBSCRIBE\n" +
          "destination:" + destination + "\n" +
          "id:" + subscriptionID + "\n"+
          "receipt:" + receiptID;
    return str;

}
string subscribe::getDestination(){
    return destination;
}