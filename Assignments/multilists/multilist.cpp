//  Name: Miro Manestar
//  Assignment number: 3
//  Assignment: Multilists
//  File name: multilist.cpp
//  Date last modified: September 19, 2020
//  Honor statement: I have neither given nor received any unauthorized help on this assignment. 

#include "multilist.h"

Multilist::Multilist(void) {
    int i = 0;
}

Multilist::Node::Node(int id, std::string name, int age): id(id), name(name), age(age) {
    this->id = id;
    this->name = name;
    this->age = age;
}

bool Multilist::insert(int id, std::string name, int age) {
    Node *node = new Node(id, name, age);
    
    first->next_id = node->prev_id;


    return true;
}

bool Multilist::remove(int id) {
    return true;
}

void Multilist::print_by_ID() {

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