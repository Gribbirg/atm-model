//
// Created by gribk on 11.04.2023.
//

#ifndef KV1_CL5_H
#define KV1_CL5_H


#include "Base.h"

class Output : public Base{
public:
    Output(Base *headObject, string objectName);

    void signal(string &message);

    void handler(string &message);
};


#endif //KV1_CL5_H
