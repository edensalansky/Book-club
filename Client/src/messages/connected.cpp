//
// Created by maiy@wincs.cs.bgu.ac.il on 07/01/2020.
//



#include "../../include/message.h"
#include "../../include/client.h"

connected::connected(string msg, client &client ) : message(msg), port(), userName(), password() {
    this->port = msg.substr(0, msg.find(":"));
    msg = msg.substr(msg.find(" ")+1);
    this->userName = msg.substr(0, msg.find(" "));
    msg = msg.substr(msg.find(" ")+1);
    this->password = msg.substr(0, msg.find(" "));
    client.setName(userName);
    setMessage(createMessage());

}

connected::~connected() {

}

connected &connected::operator=(connected &other) {
    if(&other==this)
        return *this;
    return copy(other);

}

connected &connected::copy(connected &other) {
    setMessage(other.getMessage());
    userName =other.userName;
    password =other.password;
    port =other.port;
    return *this;
}

connected::connected(connected &other) :message(other.getMessage()), port(), userName(), password() {
    copy(other);
}

string connected::createMessage() {
    string str="";
    str =str+"CONNECT\n"+
         "accept-version:1.2\n"+
         "host:stomp.cs.bgu.ac.il\n"+
         "login:"+userName+"\n"+
         "passcode:"+password;
    return str;

}

