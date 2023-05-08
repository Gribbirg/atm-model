//
// Created by gribk on 08.04.2023.
//

#ifndef KV1_BASE_H
#define KV1_BASE_H

#include <iostream>
#include <string>
#include <vector>

#define SIGNAL_D(signal_f) (TYPE_SIGNAL) (&signal_f)
#define HENDLER_D(hendler_f) (TYPE_HANDLER) (&hendler_f)

using namespace std;

class Base;

typedef void (Base::*TYPE_SIGNAL)(string&);
typedef void (Base::*TYPE_HANDLER)(string&);

class Base {
private:
    string object_name;
    Base *head_object;
    vector<Base *> subordinate_objects;
    int state;

    struct Connection {
        TYPE_SIGNAL signal;
        Base *object;
        TYPE_HANDLER handler;
    };

    vector<Connection *> connects;
public:

    Base(Base *head_object, string object_name = "Base_object");

    ~Base();

    bool set_object_name(string object_name);

    string get_object_name();

    Base *get_head_object();

    void print_subordinate_objects();

    Base *get_subordinate_object(string object_name);

    Base *find_object_in_branch(string object_name);

    Base *find_object_in_tree(string object_name);

    void print_branch();

    void print_branch_with_state();

    void set_state(int state);

    int get_state();

    bool change_head_object(Base *new_head_object);

    void del_subordinate_object(string object_name);

    Base *get_object_by_coordinate(string coordinate);

    string get_absolute_coordinate();

    void set_signal(TYPE_SIGNAL signal, Base *object, TYPE_HANDLER handler);

    void emit_signal(TYPE_SIGNAL signal, string command);

    void remove_signal(TYPE_SIGNAL signal, Base *object, TYPE_HANDLER handler);

    void set_state_for_all_objects(int state);
};

#endif //KV1_BASE_H
