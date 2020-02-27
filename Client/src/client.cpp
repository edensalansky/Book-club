//
// Created by maiy@wincs.cs.bgu.ac.il on 07/01/2020.
//

#include "../include/client.h"
#include "../include/book.h"
#include <fstream>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <mutex>
#include <message.h>
#include <ID.h>
#include "../include/connectionHandler.h"

using namespace std;

client::client(mutex &mutex) : bookMap(), ConnectedKeyBoard(true), name(), subIdMap(), ConnectedSocket(true), disconnectID(), wishlist(),Mutex(mutex){

}
client::~client() {
    for (auto &item : bookMap) {
        for (auto &book : item.second) {
            delete (book);
            book = nullptr;
        }
        item.second.clear();
    }
    bookMap.clear();
    subIdMap.clear();
    for(auto item:wishlist){
        item.first.clear();
        item.second.clear();
    }
    wishlist.clear(); // check if need to manual delete pair

}

void client::addBook(string topic, string name, bool borrow, string lenderName, bool inLibrary) {
    lock_guard<std::mutex> lock(Mutex);
    std::unordered_map<std::string, vector<book *>>::const_iterator it = bookMap.find(topic);
    if (it == bookMap.end()) {
        vector<book *> bookVector;
        bookVector.push_back(new book(name, borrow, lenderName, inLibrary));
        bookMap.insert(make_pair(topic, bookVector));
    } else {
        vector<book *> *bookVector = &(bookMap.at(topic));
        bookVector->push_back(new book(name, borrow, lenderName, inLibrary));
    }

}


void client::removeBook(string topic, string name) {
    lock_guard<std::mutex> lock(Mutex);
    unordered_map<string, vector<book *>>::const_iterator it = bookMap.find(topic);
    if (it != bookMap.end()) {
        for (book *item : it->second) {
            if (item->getName() .compare( name)==0) {
                item->setInLibrary(false);
            }

        }
    }

}

void client::returnBook(string Book, string topic) {
    lock_guard<std::mutex> lock(Mutex);
    unordered_map<string, vector<book *>>::const_iterator it = bookMap.find(topic);
    if (it != bookMap.end()) {
        for (book *item : it->second) {
            if (item->getName().compare(Book)==0) {
                item->setInLibrary(true);
            }

        }
    }

}

string client::printInventory(string topic) {
    string str = "";
    str = str + name ;
    str=str+":";
    unordered_map<string, vector<book *>>::const_iterator it = bookMap.find(topic);
    if (it != bookMap.end()) {
        for (book *item : it->second) {
            if(item->isInLibrary()) {
                str = str + item->getName()+",";
            }
        }
    }
    if(str.substr(str.size()-1).compare(":")!=0) {
        return str.substr(0, str.length() - 1);
    }
    else{
        return str;
    }

}

bool client::checkLibrary(string topic, string bookName) {
    unordered_map<string, vector<book *>>::const_iterator it = bookMap.find(topic);
    if (it != bookMap.end()) {
        for (book *item : it->second) {
            if(item->getName().compare( bookName)==0&&item->isInLibrary()){
                return true;
            }
        }
        }
    return false;
}
bool client::checkWishlist(string topic, string bookName) {
    for(pair<string,string> &item : wishlist) {
        if(item.first.compare(bookName)==0 && item.second.compare(topic)==0) {
            return true;
            }
        }
    return false;
}
void client::addToWishlist(string bookName, string topic) {
    wishlist.push_back(make_pair(bookName,topic));
}
void client::removeFromWishlist(string bookName, string topic) {
    for(pair<string,string> &item : wishlist) {
        if(item.first.compare(bookName)==0 && item.second.compare( topic ) ==0){
            item.first="";
            item.second="";
        }

    }
}

void client::addToSubIdMap(string topic, int id) {
    subIdMap.insert(make_pair(topic, id));
}

int client::getFromSubIdMap(string topic) {
    if(subIdMap.find(topic)==subIdMap.end())
        return -1;
    return subIdMap.at(topic);
}

bool client::isConnectedSocket() {
    return ConnectedSocket;
}

bool client::isConnectedKeyBoard() {
    return ConnectedKeyBoard;
}

void client::setName(string name) {
    this->name = name;
}

string client::getName() {
    return name;
}

std::unordered_map<std::string, vector<book *>> &client::getBookMap() {
    return bookMap;
}

void client::disconnectKeyBoard(string receiptID) {
    this->disconnectID = receiptID;
    ConnectedKeyBoard = false;
}

void client::disconnectSocket() {
    ConnectedSocket = false;

}

string client::getdisconnectID() {
    return disconnectID;
}

void client::removeFromSubId(string topic) {
    unordered_map<string, int>::const_iterator it = subIdMap.find(topic);
    if (it != subIdMap.end())
        subIdMap.erase(it);

}

