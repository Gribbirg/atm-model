//
// Created by gribk on 08.04.2023.
//

#include "System.h"

System::System(Base *head_object, string object_name) : Base(head_object, object_name) {}

void System::signal(string &message) {}

void System::handler(string &message) {
    enter = message;
}


void System::build_tree_objects() {

    set_object_name("system");
    auto reader = new Reader(this, "reader");
    auto control = new Control(reader, "control");
    auto init = new Init(control, "init");
    auto output = new Output(control, "output");
    auto payment = new Payment(control, "payment");
    auto deposit = new Deposit(control, "deposit");


//    reader->set_signal(SIGNAL_D(Reader::signal), this, HENDLER_D(System::handler));
//    set_signal(SIGNAL_D(System::signal), output, HENDLER_D(Output::handler));
//    set_signal(SIGNAL_D(System::signal), output, HENDLER_D(Deposit::handler));
//    init->set_signal(SIGNAL_D(Init::signal), this, HENDLER_D(System::handler));
//    init->set_signal(SIGNAL_D(Init::signal), output, HENDLER_D(Output::handler));
//    deposit->set_signal(SIGNAL_D(Deposit::signal), this, HENDLER_D(System::handler));
//    deposit->set_signal(SIGNAL_D(Deposit::signal), output, HENDLER_D(Output::handler));
//    payment->set_signal(SIGNAL_D(Payment::signal), this, HENDLER_D(System::handler));
//    payment->set_signal(SIGNAL_D(Payment::signal), output, HENDLER_D(Output::handler));
//    control->set_signal(SIGNAL_D(Control::signal), this, HENDLER_D(System::handler));

    set_signal(SIGNAL_D(System::signal), reader, HENDLER_D(Reader::handler));
    reader->set_signal(SIGNAL_D(Reader::signal), control, HENDLER_D(Control::handler));
    reader->set_signal(SIGNAL_D(Reader::signal), this, HENDLER_D(System::handler));
    control->set_signal(SIGNAL_D(Control::signal), init, HENDLER_D(Init::handler));
//    control->set_signal(SIGNAL_D(Control::signal), payment, HENDLER_D(Payment::handler));
    control->set_signal(SIGNAL_D(Control::signal), deposit, HENDLER_D(Deposit::handler));
    control->set_signal(SIGNAL_D(Control::signal), output, HENDLER_D(Output::handler));
    init->set_signal(SIGNAL_D(Init::signal), output, HENDLER_D(Output::handler));
    payment->set_signal(SIGNAL_D(Payment::signal), output, HENDLER_D(Output::handler));
    deposit->set_signal(SIGNAL_D(Deposit::signal), output, HENDLER_D(Output::handler));
    init->set_signal(SIGNAL_D(Init::signal), control, HENDLER_D(Control::handler));


}

int System::exec_app() {

    string balance;

    auto reader = (Reader *) find_object_in_tree("reader");
    auto control = (Control *) find_object_in_tree("control");
    auto init = (Init *) find_object_in_tree("init");
    auto output = (Output *) find_object_in_tree("output");
    auto payment = (Payment *) find_object_in_tree("payment");
    auto deposit = (Deposit *) find_object_in_tree("deposit");

    set_state(1);
    reader->set_state(1);

    reader->emit_signal(SIGNAL_D(Reader::signal), "");
    while (enter != "End card loading") {
        Card *card = new Card();

        for (int i = 0; i < 19; i++) {
            card->num += enter[i];
        }

        for (int i = 20; i < 24; i++) {
            card->pin += enter[i];
        }


        for (int i = 25; i < enter.size(); i++) {
            balance += enter[i];
        }
        card->balance = stoi(balance);
        balance = "";

        cards.push_back(card);

        reader->emit_signal(SIGNAL_D(Reader::signal), "");
    }

    balance = "";
    int j = 0;

    reader->emit_signal(SIGNAL_D(Reader::signal), "");
    for (int i = 0; i < 5; i++) {
        for (; j < enter.size() && enter[j] != ' '; j++) {
            balance += enter[j];
        }
        cash.push_back(stoi(balance));
        balance = "";
        j++;
    }


    reader->emit_signal(SIGNAL_D(Reader::signal), "");

    set_state_for_all_objects(8);

    string current_card;
    string current_pin;
    bool is_init = false;
    int deposit_value[5]{0, 0, 0, 0, 0};
    int deposit_sum = 0;
    string str_deposit_value;

    emit_signal(SIGNAL_D(System::signal), "Ready to work");

    reader->emit_signal(SIGNAL_D(Reader::signal), "");
    while (get_state() != 0) {

        if (enter[0] == 'I') {
            for (int i = 15; i < enter.size(); i++)
                current_card += enter[i];
            emit_signal(SIGNAL_D(System::signal), "\nEnter the PIN code");

        } else if (enter[0] == 'E') {

            current_card = "";
            is_init = false;

            emit_signal(SIGNAL_D(System::signal), "\nReady to work");

        } else if (enter[0] == 'T') {

            emit_signal(SIGNAL_D(System::signal), "\nTurn off the ATM");
            break;

        } else if (!current_card.empty() && !is_init) {

            if (enter[0] == 'P') {

                for (int i = 9; i < 13; i++)
                    current_pin += enter[i];

                init->emit_signal(SIGNAL_D(Init::signal), current_card + current_pin);

                if (enter == "\nSelect the command") is_init = true;

                current_pin = "";
            } else {

                emit_signal(SIGNAL_D(System::signal), "\nReady to work");

            }

        } else if (is_init) {

            if (enter[0] == 'D') {

                if (enter[14] == 't') {

                    for (int i: deposit_value)
                        str_deposit_value += to_string(i) + " ";

                    deposit->emit_signal(SIGNAL_D(Deposit::signal),current_card);

                    str_deposit_value = "";
                    deposit_sum = 0;
                    for (int i = 0; i < 5; i++) deposit_value[i] = 0;

                } else {

                    for (int i = 14; i < enter.size(); i++) {
                        balance += enter[i];
                    }

                    for (int ex: CASH_COST) {
                        if (ex == stoi(balance))
                            deposit->emit_signal(SIGNAL_D(Deposit::signal),
                                                 "add " + balance);
                    }
                    balance = "";
                }
            } else if (enter[0] == 'W') {

                for (int i = 15; i < enter.size(); i++)
                    balance += enter[i];

                control->emit_signal(SIGNAL_D(Control::signal), current_card + balance);
                if (enter == "good") {
                    payment->emit_signal(SIGNAL_D(Payment::signal), current_card + balance);
                }
                balance = "";
            }

        } else {

            emit_signal(SIGNAL_D(System::signal), "\nReady to work");

        }

        reader->emit_signal(SIGNAL_D(Reader::signal), "");
    }
    return 0;
}











