//  Name: Miro Manestar
//  Assignment number: 1
//  Assignment: Linked List Implementation
//  File name: llist.cpp
//  Date last modified: September 20, 2021
//  Honor statement: I have neither given nor received any unauthorized help on this assignment.

#include "llist.h"

//Node constructor initialization
LinkedList::Node::Node(const string& item) : 
    data(item), prev(nullptr), next(nullptr) { }

//LinkedList empty constructor
LinkedList::LinkedList(): head(tail), tail(head), len(0) {}

//LinkedList copy constructor
LinkedList::LinkedList(const LinkedList& other) {
    for(Node* node = other.head->next; node->next != nullptr; node = node->next) {
        Node* newNode = new Node(node->data); 

        if (head->next == nullptr) {
            head->next = newNode;
            newNode->prev = head;
        } else {
            tail->prev->next = newNode;
            newNode->prev = tail->prev;
        }

        newNode->next = tail;
        tail->prev = newNode;
    }
}

//LinkedList destructor
LinkedList::~LinkedList() {
    for (Node* node = head->next; node != nullptr; node = node->next) {
        delete node->prev;
    }

    delete tail;
}

//Creates a copy of the passed in list and returns a reference to it
//Eliminates self, creates new LinkedList from passed in list and returns it
LinkedList& LinkedList::operator=(const LinkedList& other) {
    this->~LinkedList();
    LinkedList* list = new LinkedList(other);
    return *list;
}

bool LinkedList::operator==(const LinkedList& other) const {
    return false;
}

bool LinkedList::operator!=(const LinkedList& other) const {
    return false;
}

void LinkedList::insert(const Iterator& iter, const string& item) {

}

void LinkedList::remove(Iterator& iter) {

}

int LinkedList::length() const {
    return len;
}

void LinkedList::clear() {
    this->~LinkedList();
    *this = *(new LinkedList());
}

LinkedList::Iterator::Iterator(Node* p) {
    
}