//
// Created by gribk on 03.05.2023.
//

#ifndef KV4_DEPOSIT_H
#define KV4_DEPOSIT_H


#include "Base.h"

class Deposit : public Base {
public:
    Deposit(Base *headObject, string objectName);

    void signal(string &message);

    void handler(string &message);

private:
    int add_balance[5];
};


#endif //KV4_DEPOSIT_H
