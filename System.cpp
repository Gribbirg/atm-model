//
// Created by gribk on 08.04.2023.
//

#include "System.h"

System::System(Base *head_object, string object_name) : Base(head_object, object_name) {}

void System::signal(string &message) {}

void System::signal_out(string &message) {}

void System::handler(string &message) {
    enter = message;
}

void System::handler_off(std::string &message) {
    set_state(0);
}


void System::build_tree_objects() {

    set_object_name("system");
    auto reader = new Reader(this, "reader");
    auto control = new Control(reader, "control");
    auto init = new Init(control, "init");
    auto output = new Output(control, "output");
    auto payment = new Payment(control, "payment");
    auto deposit = new Deposit(control, "deposit");

    set_signal(SIGNAL_D(System::signal), reader, HENDLER_D(Reader::handler));
    set_signal(SIGNAL_D(System::signal_out), output, HENDLER_D(Output::handler));
    reader->set_signal(SIGNAL_D(Reader::signal), this, HENDLER_D(System::handler));
    reader->set_signal(SIGNAL_D(Reader::signal), control, HENDLER_D(Control::handler));
    control->set_signal(SIGNAL_D(Control::signal_to_output), output, HENDLER_D(Output::handler));
    control->set_signal(SIGNAL_D(Control::signal_to_payment), payment, HENDLER_D(Payment::handler));
    control->set_signal(SIGNAL_D(Control::signal_to_deposit), deposit, HENDLER_D(Deposit::handler));
    control->set_signal(SIGNAL_D(Control::signal_to_deposit_add), deposit, HENDLER_D(Deposit::handler_add));
    control->set_signal(SIGNAL_D(Control::signal_to_deposit_reset), deposit, HENDLER_D(Deposit::handler_reset));
    control->set_signal(SIGNAL_D(Control::signal_to_init), init, HENDLER_D(Init::handler));
    control->set_signal(SIGNAL_D(Control::signal_to_system), this, HENDLER_D(System::handler_off));
    init->set_signal(SIGNAL_D(Init::signal), control, HENDLER_D(Control::handler_init_result));
    deposit->set_signal(SIGNAL_D(Deposit::signal), output, HENDLER_D(Output::handler));
    init->set_signal(SIGNAL_D(Init::signal), output, HENDLER_D(Output::handler));
    payment->set_signal(SIGNAL_D(Payment::signal), output, HENDLER_D(Output::handler));

}

int System::exec_app() {

    string balance;

    auto reader = (Reader *) find_object_in_tree("reader");

    set_state(1);
    reader->set_state(1);

    emit_signal(SIGNAL_D(System::signal), "");
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

        emit_signal(SIGNAL_D(System::signal), "");
    }

    balance = "";
    int j = 0;

    emit_signal(SIGNAL_D(System::signal), "");
    for (int i = 0; i < 5; i++) {
        for (; j < enter.size() && enter[j] != ' '; j++) {
            balance += enter[j];
        }
        cash.push_back(stoi(balance));
        balance = "";
        j++;
    }

    emit_signal(SIGNAL_D(System::signal), "");

    set_state_for_all_objects(8);

    emit_signal(SIGNAL_D(System::signal_out), "Ready to work");

    do {
        emit_signal(SIGNAL_D(System::signal), "");
    } while (get_state() != 0);

    return 0;
}

