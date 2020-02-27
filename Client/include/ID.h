//
// Created by maiy@wincs.cs.bgu.ac.il on 08/01/2020.
//

#ifndef CLIENT_ID_H
#define CLIENT_ID_H


#include <atomic>

class ID {

private:
    std::atomic<int> receiptId;
    std::atomic<int> subscriptionID;
public:
    ID();
    ~ID();
    int getReceiptId();
    int getSubscriptionID();

};



#endif //CLIENT_ID_H
