//
// Created by gribk on 09.04.2023.
//

#include "Reader.h"

Reader::Reader(Base *headObject, string objectName) : Base(headObject, objectName) {}

void Reader::signal_card(string &message) {
    string line;
    getline(cin, line);
    message += line;
}

void Reader::signal(string &message) {
    getline(cin, message);
}

void Reader::handler(string &message) {
    emit_signal(SIGNAL_D(Reader::signal), "");
}


