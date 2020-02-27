//
// Created by maiy@wincs.cs.bgu.ac.il on 08/01/2020.
//

#include "../../include/ID.h"

ID::ID() :receiptId(),subscriptionID() {
    receiptId = 0;
    subscriptionID = 0;
}
ID::~ID(){}
int ID::getReceiptId() {
    int id = ++receiptId;
    return id;
}
int ID::getSubscriptionID() {
    int id=++subscriptionID;
    return id;
}
