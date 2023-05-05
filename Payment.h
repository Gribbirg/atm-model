//
// Created by gribk on 11.04.2023.
//

#ifndef KV1_CL6_H
#define KV1_CL6_H


#include "Base.h"

class Payment : public Base{
public:
    Payment(Base *headObject, string objectName);

    void signal(string &message);
};


#endif //KV1_CL6_H
