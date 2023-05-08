//
// Created by gribk on 03.05.2023.
//

#include "Deposit.h"
#include "System.h"

Deposit::Deposit(Base *headObject, string objectName) : Base(headObject, objectName), sum(0) {
    for (int i = 0; i < 5; i++)
        add_balance[i] = 0;
}

void Deposit::signal(string &message) {
    message = "\n" + message;
}

void Deposit::handler(string &message) {

    string value, card_num, str_sum;

    auto system = (System *) (get_head_object()->get_head_object()->get_head_object());
    int j;

    for (j = 0; j < 19; j++)
        card_num += message[j];

    for (int i = 0; i < 5; i++) {
        system->cash[i] += add_balance[i];
    }

    for (auto card: system->cards) {
        if (card->num == card_num) {
            card->balance += sum;
            emit_signal(SIGNAL_D(Deposit::signal), "Card balance " + to_string(card->balance));
            break;
        }
    }

    for (int i = 0; i < 5; i++) add_balance[i] = 0;
    sum = 0;
}


void Deposit::handler_add(string &message) {
    for (int i = 0; i < 5; i++) {
        if (CASH_COST[i] == stoi(message)) {
            add_balance[i]++;
            sum += CASH_COST[i];
            emit_signal(SIGNAL_D(Deposit::signal), "The amount: " + to_string(sum));
            return;
        }
    }
}

void Deposit::handler_reset(string &message) {
    for (int i = 0; i < 5; i++) add_balance[i] = 0;
    sum = 0;
}
