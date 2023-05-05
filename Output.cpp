//
// Created by gribk on 11.04.2023.
//

#include "Output.h"

Output::Output(Base *headObject, string objectName) : Base(headObject, objectName) {}

void Output::signal(string &message) {
    cout << '\n' << "Signal from " << get_absolute_coordinate();
    message += " (class: 5)";
}

void Output::handler(string &message) {
    cout << message;
}
