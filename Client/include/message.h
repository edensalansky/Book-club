//
// Created by maiy@wincs.cs.bgu.ac.il on 07/01/2020.
//

#ifndef CLIENT_MESSAGE_H
#define CLIENT_MESSAGE_H

#include <iostream>
#include <string>
#include "client.h"

using namespace std;

class message {
public:
    message(string msg);

    virtual string createMessage() = 0;
    message(message &other);

    virtual ~message();

    message &operator=(message &);

    message &copy(message &other);

    string getMessage();

    void setMessage(string str);

private:
    string msg;
    int receiptID;

};

class connected : public message {
public:
    connected(string msg, client &);

    connected(connected &other);

    virtual string createMessage();

    virtual ~connected();

    connected &operator=(connected &);

    connected &copy(connected &other);

private:
    string port;
    string userName;
    string password;

};

class subscribe : public message {
public:
    subscribe(string msg, int receiptID, int subscriptionId);

    virtual string createMessage();
    subscribe(subscribe &other);
    virtual ~subscribe();

    string getDestination();

    subscribe &operator=(subscribe &);

    subscribe &copy(subscribe &other);


private:
    string receiptID;
    string subscriptionID;
    string destination;


};

class unsubscribe : public message {
public:
    unsubscribe(string msg, int receiptID, int subscriptionId);
    unsubscribe(unsubscribe &other);
    virtual string createMessage();

    string getDestination();

    virtual ~unsubscribe();

    unsubscribe &operator=(unsubscribe &);

    unsubscribe &copy(unsubscribe &other);


private:
    string receiptID;
    string subscriptionID;
    string destination;

};

class Send : public message {
public:
    Send(string msg, int subscriptionId, string command, client &);
    Send(Send &other);
    virtual string createMessage();

    string getDestination();

    Send &operator=(Send &);

    virtual ~Send();

    Send &copy(Send &other);

private:
    string subscriptionID;
    string destination;
    string command;
    string bookName;
    client *Client;


};

class disconnect : public message {
private:
    client *Client;
    string receiptId;

public:
    disconnect(string msg, int receiptId, client &);
    disconnect(disconnect &other);
    virtual string createMessage();

    virtual ~disconnect();

    disconnect &operator=(disconnect &);

    disconnect &copy(disconnect &other);
};

class status : public message {
private:
    string destination;
    string inventory;
    string subscriptionId;
    client *Client;
public:
    status(string msg, string destination, string subscriptionId, client &);
    status(status &other);
    virtual string createMessage();

    virtual ~status();

    status &operator=(status &);

    status &copy(status &other);
};


#endif //CLIENT_MESSAGE_H
