//
// Created by gribk on 08.04.2023.
//

#ifndef KV1_APPLICATIONCLASS_H
#define KV1_APPLICATIONCLASS_H


#include "Base.h"
#include "Reader.h"
#include "Control.h"
#include "Init.h"
#include "Output.h"
#include "Payment.h"
#include "Deposit.h"

const int CASH_COST[5] {5000, 2000, 1000, 500, 100};

class System : public Base {
public:
    System(Base *head_object, string object_name = "Object_name");

    void build_tree_objects();

    int exec_app();

    void signal(string &message);

    void signal_out(string &message);

    void handler(string &message);

    void handler_off(string &message);

    struct Card {
        string num;
        string pin;
        int balance;
    };

    vector<Card *> cards;

    vector<int> cash;


private:
    string enter;
};


#endif //KV1_APPLICATIONCLASS_H
