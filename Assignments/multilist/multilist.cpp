//  Name: Miro Manestar
//  Assignment number: 3
//  Assignment: Multilists
//  File name: multilist.cpp
//  Date last modified: September 19, 2020
//  Honor statement: I have neither given nor received any unauthorized help on this assignment. 

#include "multilist.h"

Multilist::Multilist(void) {
    //Multilist *multilist = new Multilist;
}

Multilist::~Multilist(void) {

}

Multilist::Node::Node(int id, std::string name, int age): id(id), name(name), age(age) {

}

bool Multilist::insert(int id, std::string name, int age) {
    Node *node = new Node(id, name, age);
    
    if(first->next_id == nullptr) {
        first->next_id = node;
    }
    if(first->next_age == nullptr) {
        first->next_age = node;
    }
    if(first->next_name == nullptr) {
        first->next_name = node;
    }



    return true;
}

bool Multilist::remove(int id) {
    return true;
}

void Multilist::print_by_ID() {
    std::string print;
    while(first->next_id != nullptr) {
        int temp = first->next_id;
        print += std::to_string(temp);
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