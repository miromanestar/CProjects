//  Name: Miro Manestar
//  Assignment number: 3
//  Assignment: Multilists
//  File name: multilist.cpp
//  Date last modified: September 19, 2020
//  Honor statement: I have neither given nor received any unauthorized help on this assignment. 

#include "multilist.h"
#include <iostream>

Multilist::Multilist(void) {
    //Multilist *multilist = new Multilist;
}

Multilist::~Multilist(void) {

}

Multilist::Node::Node(int id, std::string name, int age): id(id), name(name), age(age) {
    if(id == NULL) { this->id = 0; }
    if(name == "") { this->name = "NULL"; }
    if(age == NULL) { this->age = 0; }

    this->next_age = nullptr;
    this->next_id = nullptr;
    this->next_name = nullptr;

    this->prev_age = nullptr;
    this->next_id = nullptr;
    this->prev_name = nullptr;
}

bool Multilist::insert(int id, std::string name, int age) {
    Node *node = new Node(id, name, age);
    node->next_id = nullptr;
    node->next_age = nullptr;
    node->next_name = nullptr;
    
    first->next_id = node;



    return true;
}

bool Multilist::remove(int id) {
    return true;
}

void Multilist::print_by_ID() {
    std::string print;
    for (Node *p = first; p != nullptr; p = p->next_id) {
        std::cout << p->id << ' ';
    }
}

void Multilist::print_by_ID_reverse() {

}

void Multilist::print_by_name() {

}

void Multilist::print_by_name_reverse() {

}

void Multilist::print_by_age() {

}

void Multilist::print_by_age_reverse() {

}