//
// Created by gribk on 08.04.2023.
//

#ifndef KV1_CL3_H
#define KV1_CL3_H


#include "Base.h"

class Control : public Base {
private:
    string current_card;
    bool init_finish;
public:
    Control(Base *headObject, string objectName);

    void signal_to_output(string &message);

    void signal_to_init(string &message);

    void signal_to_deposit(string &message);

    void signal_to_deposit_add(string &message);

    void signal_to_deposit_reset(string &message);

    void signal_to_system(string &message);

    void signal_to_payment(string &message);

    void handler(string &message);

    void handler_init_result(string &message);
};


#endif //KV1_CL3_H
