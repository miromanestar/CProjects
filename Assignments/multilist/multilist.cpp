//  Name: Miro Manestar
//  Assignment number: 3
//  Assignment: Multilists
//  File name: multilist.cpp
//  Date last modified: September 19, 2020
//  Honor statement: I have neither given nor received any unauthorized help on this assignment. 

#include "multilist.h"
#include <iostream>

Multilist::Multilist() { }

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
    
    for (Node *p = first; p != nullptr; p = p->next_id) {
        if (p->next_id == nullptr) {
            node->prev_id = p;
            p->next_id = node;

            node->next_id = last;
        }
    }
    for (Node *p = first; p != nullptr; p = p->next_name) {
        if (p->next_name == nullptr) {
            node->prev_name = p;
            p->next_name = node;

            node->next_name = last;
        }
    }
    for (Node *p = first; p != nullptr; p = p->next_age) {
        if (p->prev_age == nullptr) {
            node->prev_age = p;
            p->next_age = node;

            node->next_age = last;
        }
    }

    return true;
}

bool Multilist::remove(int id) {
    return true;
}

void Multilist::print_by_ID() {
    for (Node *p = first; p != nullptr; p = p->next_id) {
        std::cout << '(' << p->name << ',' << p->id << ',' << p->age << ")\n";
    }
}

void Multilist::print_by_ID_reverse() {
    for (Node *p = last; p != nullptr; p = p->prev_id) {
        std::cout << '(' << p->name << ',' << p->id << ',' << p->age << ")\n";
    }
}

void Multilist::print_by_name() {
    for (Node *p = first; p != nullptr; p = p->next_name) {
        std::cout << '(' << p->name << ',' << p->id << ',' << p->age << ")\n";
    }
}

void Multilist::print_by_name_reverse() {
    for (Node *p = last; p != nullptr; p = p->prev_name) {
        std::cout << '(' << p->name << ',' << p->id << ',' << p->age << ")\n";
    }
}

void Multilist::print_by_age() {
    for (Node *p = first; p != nullptr; p = p->next_age) {
        std::cout << '(' << p->name << ',' << p->id << ',' << p->age << ")\n";
    }
}

void Multilist::print_by_age_reverse() {
    for (Node *p = last; p != nullptr; p = p->prev_age) {
        std::cout << '(' << p->name << ',' << p->id << ',' << p->age << ")\n";
    }
}