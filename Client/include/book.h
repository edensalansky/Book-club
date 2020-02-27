//
// Created by maiy@wincs.cs.bgu.ac.il on 07/01/2020.

#ifndef CLIENT_BOOK_H
#define CLIENT_BOOK_H
#include <fstream>
using namespace std;
class book {

public:

    book(const string &name, bool borrow, const string &lenderName, bool exist);

    const string &getName() const;
    bool isBorrow() const;
    bool isInLibrary() const;
    const string &getLenderName() const;
    void setName(const string &name);
    void setBorrow(bool borrow);
    void setLenderName(const string &lenderName);
    void setInLibrary(bool exist);

private:
    string name;
    bool borrow;
    string lenderName;
    bool inLibrary;






};


#endif //CLIENT_BOOK_H
