//  Name: Miro Manestar
//  Assignment number: 3
//  Assignment: Multilists
//  File name: multilist.cpp
//  Date last modified: September 19, 2020
//  Honor statement: I have neither given nor received any unauthorized help on this assignment. 

#include "multilist.h"
#include <iostream>

Multilist::Multilist(): first(new Node(0, "", 0)), last(new Node(0, "", 0)) { 
    first->next_age = last;
    first->next_id = last;
    first->next_name = last;

    last->prev_age = first;
    last->prev_id = first;
    last->prev_name = first;
}

Multilist::~Multilist() { }

Multilist::Node::Node(int id, std::string name, int age): id(id), name(name), age(age) {
    this->next_id = nullptr;
    this->next_age = nullptr;
    this->next_name = nullptr;
    
    this->prev_id = nullptr;
    this->next_age = nullptr;
    this->prev_name = nullptr;
}

bool Multilist::insert(int id, std::string name, int age) {
    Node *node = new Node(id, name, age);

    //If list is essentially empty, then simply plop it in there and leave
    if(first->next_id == last) {
        first->next_id = node;
        first->next_name = node;
        first->next_age = node;

        node->prev_id = first;
        node->prev_name = first;
        node->prev_age = first;

        node->next_id = last;
        node->next_name = last;
        node->next_age = last;

        last->prev_id = node;
        last->prev_name = node;
        last->prev_age = node;

        return true;
    }

    //But if it's not empty, now we have to determine order... fun...
    for (Node *p = first->next_id; p != last; p = p->next_id) {
        int current = p->id;
        int next = p->next_id->id;
        if(current <= id && next <= id) {
            node->prev_id = p;
            node->next_id = p->next_id;

            p->next_id->prev_id = node;
            p->next_id = node;
        }
    }

    return true;
}

bool Multilist::remove(int id) {
    return true;
}

void Multilist::print_by_ID() {
    for (Node *p = first->next_id; p != last; p = p->next_id) {
        std::cout << '(' << p->name << ',' << p->id << ',' << p->age << ")\n";
    }
}

void Multilist::print_by_ID_reverse() {
    for (Node *p = last->prev_id; p != first; p = p->prev_id) {
        std::cout << '(' << p->name << ',' << p->id << ',' << p->age << ")\n";
    }
}

void Multilist::print_by_name() {
    for (Node *p = first->next_name; p != last; p = p->next_name) {
        std::cout << '(' << p->name << ',' << p->id << ',' << p->age << ")\n";
    }
}

void Multilist::print_by_name_reverse() {
    for (Node *p = last->prev_name; p != first; p = p->prev_name) {
        std::cout << '(' << p->name << ',' << p->id << ',' << p->age << ")\n";
    }
}

void Multilist::print_by_age() {
    for (Node *p = first->next_age; p != last; p = p->next_age) {
        std::cout << '(' << p->name << ',' << p->id << ',' << p->age << ")\n";
    }
}

void Multilist::print_by_age_reverse() {
    for (Node *p = last->prev_age; p != first; p = p->prev_age) {
        std::cout << '(' << p->name << ',' << p->id << ',' << p->age << ")\n";
    }
}