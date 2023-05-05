//
// Created by gribk on 08.04.2023.
//

#include "Control.h"
#include "System.h"

Control::Control(Base *headObject, string object_name) : Base(headObject, object_name), setup_finish(false) {}

void Control::signal(string &message) {
    auto system = (System *) get_head_object();
    string card_num, str_value;
    int j, value;

    for (j = 0; j < 19; j++)
        card_num += message[j];

    for (; j < message.size(); j++)
        str_value += message[j];
    value = stoi(str_value);

    if (value % 100 != 0) {
        message = "\nThe amount is not a multiple of 100";
        return;
    }

    for (auto card: system->cards) {
        if (card->num == card_num) {
            if (card->balance < value) {
                message = "\nThere is not enough money on the card";
            }
            return;
        }
    }
    message = "good";
}

void Control::handler(string &message) {
    if (setup_finish) {



    } else {



    }

}
