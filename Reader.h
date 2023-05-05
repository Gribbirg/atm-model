//
// Created by gribk on 09.04.2023.
//

#ifndef KV1_CL2_H
#define KV1_CL2_H


#include "Base.h"

class Reader : public Base{
public:
    Reader(Base *headObject, string objectName);

    void signal_card(string &message);

    void signal_cash(string &message);

    void signal(string &message);

    void handler(string &message);
};


#endif //KV1_CL2_H
