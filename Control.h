//
// Created by gribk on 08.04.2023.
//

#ifndef KV1_CL3_H
#define KV1_CL3_H


#include "Base.h"

class Control : public Base {
private:
    bool setup_finish;
public:
    Control(Base *headObject, string objectName);

    void signal(string &message);

    void handler(string &message);
};


#endif //KV1_CL3_H
