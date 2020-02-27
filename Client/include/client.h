//
// Created by maiy@wincs.cs.bgu.ac.il on 07/01/2020.
//

#ifndef CLIENT_CLIENT_H
#define CLIENT_CLIENT_H

#include <iostream>
#include <unordered_map>
#include <fstream>
#include "../include/book.h"
#include "ID.h"
#include "connectionHandler.h"
#include <bits/unordered_map.h>
#include <map>
#include <vector>
#include <mutex>
using namespace std;

class client {
public:
    client(mutex& );
    ~client();
    void addBook(string topic, string name , bool borrow, string lenderName, bool inLibrary);
    bool isConnectedKeyBoard();
    bool isConnectedSocket();
    void returnBook(string Book, string topic);
    string printInventory(string topic);
    void lendBook();
    void setName (string name);
    string getName();
    std::unordered_map<std::string, vector<book*>> &getBookMap();
    void removeBook(string topic, string name);
    void addToSubIdMap(string topic, int id);
    int getFromSubIdMap(string topic);
    void disconnectKeyBoard(string);
    void disconnectSocket();
    string getdisconnectID();
    void removeFromSubId(string);
    bool checkLibrary(string topic, string bookName);
    void addToWishlist(string bookName, string topic);
    void removeFromWishlist(string bookName, string topic);
    bool checkWishlist(string topic, string bookName);



private:
    unordered_map<string,vector<book*>>bookMap;
    bool ConnectedKeyBoard;
    string name;
    unordered_map<string, int> subIdMap;
    bool ConnectedSocket;
    string disconnectID;
    vector<pair<string,string>> wishlist;
    mutex &Mutex;
};


#endif //CLIENT_CLIENT_H
