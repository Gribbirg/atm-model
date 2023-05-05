//
// Created by gribk on 08.04.2023.
//

#include "Control.h"
#include "System.h"

Control::Control(Base *headObject, string object_name) :
        Base(headObject, object_name),
        init_finish(false),
        current_card("") {}

void Control::signal(string &message) {
    auto system = (System *) (get_head_object()->get_head_object());
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

    string balance;

    if (message[0] == 'I') {
        for (int i = 15; i < message.size(); i++)
            current_card += message[i];
        emit_signal(SIGNAL_D(Control::signal), "O\nEnter the PIN code");

    } else if (message[0] == 'E') {

        current_card = "";
        init_finish = false;

        emit_signal(SIGNAL_D(Control::signal), "O\nReady to work");

    } else if (message[0] == 'T') {

        emit_signal(SIGNAL_D(Control::signal), "O\nTurn off the ATM");
        return;

    } else if (!current_card.empty() && !init_finish) {

        if (message[0] == 'P') {

            string current_pin;
            for (int i = 9; i < 13; i++)
                current_pin += message[i];

            emit_signal(SIGNAL_D(Control::signal), "I" + current_card + current_pin);

            if (message == "\nSelect the command") init_finish = true;

            current_pin = "";
        } else {

            emit_signal(SIGNAL_D(Control::signal), "O\nReady to work");

        }

    } else if (init_finish) {

        if (message[0] == 'D') {

            if (message[14] == 't') {

                emit_signal(SIGNAL_D(Control::signal), "D" + current_card);

            } else {

                for (int i = 14; i < message.size(); i++) {
                    balance += message[i];
                }

                emit_signal(SIGNAL_D(Control::signal), "D add" + balance);

                balance = "";
            }
        } else if (message[0] == 'W') {

            for (int i = 15; i < message.size(); i++)
                balance += message[i];

            emit_signal(SIGNAL_D(Control::signal), current_card + balance);

            balance = "";
        }

    } else {

        emit_signal(SIGNAL_D(Control::signal), "O\nReady to work");

    }

    emit_signal(SIGNAL_D(Control::signal), "R");
}

