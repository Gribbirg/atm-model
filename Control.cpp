//
// Created by gribk on 08.04.2023.
//

#include "Control.h"
#include "System.h"

Control::Control(Base *headObject, string object_name) :
        Base(headObject, object_name),
        init_finish(false),
        current_card("") {}

void Control::signal_to_output(string &message) {
    message = '\n' + message;
}

void Control::signal_to_init(string &message) {
    message = current_card + message;
}

void Control::signal_to_deposit(string &message) {
    message = current_card;
}

void Control::signal_to_system(string &message) {}

void Control::signal_to_deposit_add(string &message) {}

void Control::signal_to_deposit_reset(string &message) {}

void Control::signal_to_payment(string &message) {
    message = current_card + message;
}

void Control::handler(string &message) {

    auto system = (System *) (get_head_object()->get_head_object());
    string balance;

    if (message[0] == 'I') {

        current_card = "";

        for (int i = 15; i < message.size(); i++)
            current_card += message[i];

        emit_signal(SIGNAL_D(Control::signal_to_output), "Enter the PIN code");

    } else if (message[0] == 'E') {

        current_card = "";
        init_finish = false;
        emit_signal(SIGNAL_D(Control::signal_to_deposit_reset), "");

        emit_signal(SIGNAL_D(Control::signal_to_output), "Ready to work");

    } else if (message[0] == 'T') {

        emit_signal(SIGNAL_D(Control::signal_to_output), "Turn off the ATM");
        emit_signal(SIGNAL_D(Control::signal_to_system), "");
        return;


    } else if (message[0] == 'S') {

        system->print_branch_with_state();
        emit_signal(SIGNAL_D(Control::signal_to_system), "");
        return;

    } else if (!current_card.empty() && !init_finish) {

        if (message[0] == 'P') {

            string current_pin;
            for (int i = 9; i < 13; i++)
                current_pin += message[i];

            emit_signal(SIGNAL_D(Control::signal_to_init),  current_pin);

        } else {

            emit_signal(SIGNAL_D(Control::signal_to_output), "Ready to work");

        }

    } else if (init_finish) {

        if (message[0] == 'D') {

            if (message[14] == 't') {

                emit_signal(SIGNAL_D(Control::signal_to_deposit), "");

            } else {

                for (int i = 14; i < message.size(); i++) {
                    balance += message[i];
                }

                emit_signal(SIGNAL_D(Control::signal_to_deposit_add), balance);
            }
        } else if (message[0] == 'W') {

            for (int i = 15; i < message.size(); i++)
                balance += message[i];

            string card_num, str_value;
            int value;

            value = stoi(balance);

            if (value % 100 != 0) {
                emit_signal(SIGNAL_D(Control::signal_to_output), "The amount is not a multiple of 100");
                return;
            }

            for (auto card: system->cards) {
                if (card->num == current_card) {
                    if (card->balance < value) {
                        emit_signal(SIGNAL_D(Control::signal_to_output), "There is not enough money on the card");
                        return;
                    }
                }
            }

            emit_signal(SIGNAL_D(Control::signal_to_payment), balance);
        }

    } else {

        emit_signal(SIGNAL_D(Control::signal_to_output), "Ready to work");

    }
}

void Control::handler_init_result(string &message) {
    if (message == "\nSelect the command")
        init_finish = true;
}

