//  Name: Miro Manestar
//  Assignment number: 3
//  Assignment: Multilists
//  File name: multilist.cpp
//  Date last modified: September 22, 2020
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

Multilist::~Multilist() { 
    delete this;
}

Multilist::Node::Node(int id, std::string name, int age): id(id), name(name), age(age) {
    this->next_id = nullptr;
    this->next_age = nullptr;
    this->next_name = nullptr;
    
    this->prev_id = nullptr;
    this->next_age = nullptr;
    this->prev_name = nullptr;
}

//Checks if a string contains only letters
static bool isAlpha(std::string str) {
    for (char letter : str) {
        if(!std::isalpha(letter)) {
            return false;
        }
    }
    
    return true;
}

//Converts string to uppercase
static std::string upper(std::string str) {
    std::string temp;
    for (std::string::size_type i=0; i<str.length(); ++i)
        temp += std::toupper(str[i]);
    return temp;
}

bool Multilist::insert(int id, std::string name, int age) {
    //Checks if name only has letters
    if(!isAlpha(name)) {
        return false;
    }

    name = upper(name);
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
    //Determine where to insert by id
    for (Node *p = first; p != last; p = p->next_id) {
        int next = p->next_id->id;
        if(id == next) {
            return false;
        }

        if(id < next || p->next_id == last) {
            node->prev_id = p;
            node->next_id = p->next_id;

            p->next_id->prev_id = node;
            p->next_id = node;

            break;
        }
    }

    //Determine where to insert by age
    for (Node *p = first; p != last; p = p->next_age) {
        int next = p->next_age->age;
        if(age <= next || p->next_age == last) {
            node->prev_age = p;
            node->next_age = p->next_age;

            p->next_age->prev_age = node;
            p->next_age = node;

            break;
        }
    }

    //Determine where to insert by name
    for (Node *p = first; p != last; p = p->next_name) {
        std::string next = upper(p->next_name->name);
        if(name.compare(next) <= 0 || p->next_name == last) {
            node->prev_name = p;
            node->next_name = p->next_name;

            p->next_name->prev_name = node;
            p->next_name = node;

            break;
        }
    }

    return true;
}

bool Multilist::remove(int id) {
    for (Node *p = first; p != last; p = p->next_id) {
        if(id == p->id && (p != first && p != last)) {

            //Relink by ID
            p->prev_id->next_id = p->next_id;
            p->next_id->prev_id = p->prev_id; 

            //Relink by name
            p->prev_name->next_name = p->next_name;
            p->next_name->prev_name = p->prev_name;

            //Relink by age
            p->prev_age->next_age = p->next_age;
            p->next_age->prev_age = p->prev_age;

            delete p;

            return true;
        }
    }

    return false;
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