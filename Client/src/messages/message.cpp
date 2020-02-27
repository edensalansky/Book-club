//
// Created by maiy@wincs.cs.bgu.ac.il on 07/01/2020.
//

#include "../../include/message.h"

message::message(string message) : msg(message),receiptID(0) {
}


 message::~message(){}

message &message::operator=(message &other) {
    if(&other==this)
        return *this;
    return copy(other);
}

message::message(message &other):msg(other.getMessage()),receiptID() {
    copy(other);

}

message &message::copy(message &other) {
    setMessage(other.getMessage());
    receiptID =other.receiptID;
    msg =other.msg;
    return *this;
}

string message::getMessage() {
    return msg;
}
void message::setMessage(string str){
    msg = str;
}
