//
// Created by gribk on 08.04.2023.
//

#include "Base.h"

Base::Base(Base *head_object, string object_name) {
    this->head_object = head_object;
    state = 0;
    if (!set_object_name(object_name)) {
        delete this;
        return;
    }
    if (head_object)
        head_object->subordinate_objects.push_back(this);
}

Base::~Base() {
    for (Base *object: subordinate_objects)
        delete object;
}

bool Base::set_object_name(string object_name) {
    if (head_object) {
        if (head_object->get_subordinate_object(object_name))
            return false;
    }
    this->object_name = object_name;
    return true;
}

string Base::get_object_name() {
    return object_name;
}

Base *Base::get_head_object() {
    return head_object;
}

void Base::print_subordinate_objects() {
    if (subordinate_objects.empty()) return;

    cout << '\n' << object_name;

    for (Base *object: subordinate_objects)
        cout << "  " << object->get_object_name();
    subordinate_objects.back()->print_subordinate_objects();
}

Base *Base::get_subordinate_object(string object_name) {
    for (Base *object: subordinate_objects) {
        if (object->get_object_name() == object_name) {
            return object;
        }
    }
    return nullptr;
}

Base *Base::find_object_in_branch(string object_name) {
    if (this->object_name == object_name)
        return this;
    if (subordinate_objects.empty())
        return nullptr;

    Base *ans = nullptr;
    Base *current;


    for (auto object: subordinate_objects) {
        current = object->find_object_in_branch(object_name);
        if (current && ans)
            return nullptr;
        if (current)
            ans = current;
        else if (object->get_subordinate_object(object_name))
            return nullptr;
    }
    return ans;
}

Base *Base::find_object_in_tree(string object_name) {
    if (head_object)
        return head_object->find_object_in_tree(object_name);
    return find_object_in_branch(object_name);
}

void Base::print_branch() {
    int distance = 0;
    Base *h_object = head_object;
    while (h_object) {
        distance++;
        h_object = h_object->get_head_object();
    }

    cout << '\n' << string(distance * 4, ' ') << object_name;
    for (auto object: subordinate_objects) {
        object->print_branch();
    }
}

void Base::set_state(int state) {
    if (state == 0) {
        for (auto object: subordinate_objects)
            object->set_state(0);
    } else if (this->state == 0) {
        Base *h_object = head_object;
        while (h_object) {
            if (h_object->state == 0)
                return;
            h_object = h_object->get_head_object();
        }
    }
    this->state = state;
}

void Base::print_branch_with_state() {
    int distance = 0;
    Base *h_object = head_object;
    while (h_object) {
        distance++;
        h_object = h_object->get_head_object();
    }

    cout << '\n' << string(distance * 4, ' ') << object_name;
    if (state == 0)
        cout << " is not ready";
    else
        cout << " is ready";

    for (auto object: subordinate_objects) {
        object->print_branch_with_state();
    }
}

bool Base::change_head_object(Base *new_head_object) {
    if (
            !head_object ||
            !new_head_object ||
            new_head_object->get_subordinate_object(object_name)
            )
        return false;

    Base *current_object = new_head_object;
    while (current_object) {
        current_object = current_object->get_head_object();
        if (current_object == this) return false;
    }

    for (int i = 0; i < head_object->subordinate_objects.size(); i++) {
        if (head_object->subordinate_objects[i] == this) {
            head_object->subordinate_objects.erase(head_object->subordinate_objects.begin() + i);
            break;
        }
    }

    head_object = new_head_object;
    head_object->subordinate_objects.push_back(this);

    return true;
}

void Base::del_subordinate_object(string object_name) {
    Base *object = get_subordinate_object(object_name);

    if (!object) return;

    for (int i = 0; i < subordinate_objects.size(); i++) {
        if (subordinate_objects[i] == object) {
            subordinate_objects.erase(subordinate_objects.begin() + i);
            break;
        }
    }

    for (auto subordinate_object: object->subordinate_objects) {
        subordinate_object->change_head_object(this);
    }

    delete object;
}

Base *Base::get_object_by_coordinate(string coordinate) {
    Base *current_object = this;
    if (coordinate[0] == '.') {

        if (coordinate.size() == 1) return this;

        return find_object_in_branch(
                coordinate.substr(1, coordinate.size() - 1)
        );

    } else if (coordinate[0] == '/') {

        while (current_object->get_head_object()) {
            current_object = current_object->get_head_object();
        }

        if (coordinate.size() == 1) return current_object;

        coordinate = coordinate.substr(1, coordinate.size() - 1);

        if (coordinate[0] == '/')
            return current_object->find_object_in_branch(
                    coordinate.substr(1, coordinate.size() - 1)
            );
    }

    string current_object_name;
    for (char sym: coordinate) {
        if (sym == '/') {

            current_object = current_object->get_subordinate_object(
                    current_object_name
            );
            if (!current_object) return nullptr;

            current_object_name = "";

        } else {
            current_object_name += sym;
        }
    }

    current_object = current_object->get_subordinate_object(
            current_object_name
    );
    if (!current_object) return nullptr;

    return current_object;
}

string Base::get_absolute_coordinate() {
    if (!head_object) return "/";

    string coordinate = '/' + object_name;
    Base *current_object = get_head_object();

    while (current_object->get_head_object()) {
        coordinate.insert(0, '/' + current_object->get_object_name());
        current_object = current_object->get_head_object();
    }

    return coordinate;
}

void Base::set_signal(TYPE_SIGNAL signal, Base *object, TYPE_HANDLER handler) {

    for (Connection *connect: connects) {
        if (
                connect->signal == signal &&
                connect->object == object &&
                connect->handler == handler
                )
            return;
    }

    Connection *connection = new Connection;
    connection->handler = handler;
    connection->object = object;
    connection->signal = signal;

    connects.push_back(connection);
}

void Base::emit_signal(TYPE_SIGNAL signal, string command) {

    if (state == 0) return;

    TYPE_HANDLER handler;
    Base *object;

    (this->*signal)(command);

    for (Connection *connect: connects) {
        if (connect->signal == signal && connect->object->state != 0) {
            handler = connect->handler;
            object = connect->object;
            (object->*handler)(command);
        }
    }
}

void Base::remove_signal(TYPE_SIGNAL signal, Base *object, TYPE_HANDLER handler){
    for (int i = 0; i < connects.size(); i++) {
        if (
                connects[i]->signal == signal &&
                connects[i]->object == object &&
                connects[i]->handler == handler
                ) {
            delete connects[i];
            connects.erase(connects.begin() + i);
        }
    }
}

void Base::set_state_for_all_objects(int state) {
    this->state = state;
    for (auto object : subordinate_objects)
        object->set_state_for_all_objects(state);
}

int Base::get_state() {
    return state;
}

