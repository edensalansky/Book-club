//
// Created by maiy@wincs.cs.bgu.ac.il on 07/01/2020.
//

#include "../include/book.h"

book::book(const string &name, bool borrow, const string &lenderName, bool inLibrary) :
        name(name), borrow(borrow), lenderName(lenderName), inLibrary(inLibrary) {}

const string &book::getName() const {
    return name;
}

bool book::isBorrow() const {
    return borrow;
}

bool book::isInLibrary() const {
    return inLibrary;
}

const string &book::getLenderName() const {
return lenderName;
}

void book::setName(const string &name) {
   this->name = name;
}

void book::setBorrow(bool borrow) {
    this->borrow = borrow;
}

void book::setLenderName(const string &lenderName) {
    this->lenderName = lenderName;
}

void book::setInLibrary(bool exist) {
    this->inLibrary = exist;
}
