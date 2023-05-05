//
// Created by gribk on 11.04.2023.
//

#include "Payment.h"
#include "System.h"

Payment::Payment(Base *headObject, string objectName) : Base(headObject, objectName) {}

void Payment::signal(string &message) {
    auto system = (System *) (get_head_object()->get_head_object()->get_head_object());
    string card_num, str_value;
    int j, value;

    for (j = 0; j < 19; j++)
        card_num += message[j];

    for (; j < message.size(); j++)
        str_value += message[j];
    value = stoi(str_value);

    vector<int> cash = system->cash;
    vector<int> usage;
    for (int i = 0; i < 5; i++) {
        usage.push_back(0);

        while (cash[i] > 0 && value >= CASH_COST[i]) {
            usage[i]++;
            cash[i]--;
            value -= CASH_COST[i];
        }
    }

    if (value != 0) {
        message = "\nThere is not enough money in the ATM";
        return;
    }

    value = stoi(str_value);

    for (auto card: system->cards) {
        if (card->num == card_num) {
            system->cash = cash;
            card->balance -= value;
            message = "\nTake the money: 5000 * " + to_string(usage[0])
                      + " rub., 2000 * " + to_string(usage[1])
                      + " rub., " + to_string(usage[2])
                      + " rub., 500 * " + to_string(usage[3])
                      + " rub., 100 * " + to_string(usage[4]) + " rub.";
            break;
        }
    }
}

void Payment::handler(string &message) {
    emit_signal(SIGNAL_D(Payment::signal), message);
}



