//
// Created by gribk on 03.05.2023.
//

#include "Deposit.h"
#include "System.h"

Deposit::Deposit(Base *headObject, string objectName) : Base(headObject, objectName) {
    for (int i = 0; i < 5; i++)
        add_balance[i] = 0;
}

void Deposit::signal(string &message) {

    string value;
    int sum = 0;

    if (message[0] == 'a' && message[1] == 'd' && message[2] == 'd') {

        for (int i = 4; i < message.size(); i++) {
            value += message[i];
        }

        for (int i = 0; i < 5; i++) {
            if (CASH_COST[i] == stoi(value)) {
                add_balance[i]++;
            }
            sum += add_balance[i] * CASH_COST[i];
        }

        message = "\nThe amount: " + to_string(sum);

    } else {

        auto system = (System *) get_head_object();
        string card_num, str_sum;
        int j;

        for (j = 0; j < 19; j++)
            card_num += message[j];

        for (int i = 0; i < 5; i++) {
            system->cash[i] += add_balance[i];
            sum += add_balance[i] * CASH_COST[i];
        }

        for (auto card: system->cards) {
            if (card->num == card_num) {
                card->balance += sum;
                message = "\nCard balance " + to_string(card->balance);
                break;
            }
        }

        for (int i = 0; i < 5; i++)
            add_balance[i] = 0;
    }
}

void Deposit::handler(string &message) {
    if (message[1] == 'R' || message[1] == 'E') {
        for (int i = 0; i < 5; i++)
            add_balance[i] = 0;
    }
}