//
// Created by gribk on 11.04.2023.
//

#ifndef KV1_CL4_H
#define KV1_CL4_H


#include "Base.h"

class Init : public Base{
public:
    Init(Base *headObject, string objectName);

    void signal(string &message);

    void handler(string &message);
};


#endif //KV1_CL4_H
