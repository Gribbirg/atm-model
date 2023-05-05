//
// Created by gribk on 11.04.2023.
//

#include "Init.h"
#include "System.h"

Init::Init(Base *headObject, string objectName) : Base(headObject, objectName) {}

void Init::signal(string &message) {
    string card_num, pin;
    for (int i = 0; i < 19; i++)
        card_num += message[i];
    for (int i = 19; i < 23; i++)
        pin += message[i];

    auto system = (System *)get_head_object();
    for (auto card : system->cards) {
        if (card->num == card_num && card->pin == pin) {
            message = "\nSelect the command";
            break;
        }
    }
}

void Init::handler(string &message) {
    cout << '\n' << "Signal to " << get_absolute_coordinate() << "   Text: " << message;
}
