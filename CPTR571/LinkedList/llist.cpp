//  Name: Miro Manestar
//  Assignment number: 1
//  Assignment: Linked List Implementation
//  File name: llist.cpp
//  Date last modified: September 28, 2021
//  Honor statement: I have neither given nor received any unauthorized help on this assignment.

#include "llist.h"

//Node constructor initialization
LinkedList::Node::Node(const string& item) : 
    data(item), next(nullptr), prev(nullptr) { }

//LinkedList empty constructor
LinkedList::LinkedList() : 
    head(new Node(std::string())), tail(new Node(std::string())), len(0) {

    head->next = tail;
    tail->prev = head;
}

//LinkedList copy constructor
LinkedList::LinkedList(const LinkedList& other) :
    head(new Node(std::string())), tail(new Node(std::string())), len(0) {
    
    head->next = tail;
    tail->prev = head;

    if (other.length() == 0)
        return;

    for(Iterator i = other.begin(); i != other.end(); i++) {
        insert(end(), *i);
    }

}

//LinkedList destructor
LinkedList::~LinkedList() {
    clear();
    delete head;
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
    if (length() != other.length())
        return false;

    Iterator i1 = begin();
    Iterator i2 = other.begin();

    while (i1 != end()) {
        if ((*i1).compare(*i2) != 0)
            return false;
        i1++; i2++;
    }

    return true;
}

bool LinkedList::operator!=(const LinkedList& other) const {
    return !(*this == other);
}

void LinkedList::insert(const Iterator& iter, const string& item) {
    Node* node = new Node(item);
    node->prev = iter.ptr->prev;
    node->next = iter.ptr;

    iter.ptr->prev->next = node;
    iter.ptr->prev = node;

    len++;
}

void LinkedList::remove(Iterator& iter) {
    if (length() == 0 || iter == end() || iter == --begin())
        return;

    Node* node = iter.ptr;

    node->prev->next = node->next;
    node->next->prev = node->prev;

    delete node;
    len--;
}

LinkedList::Iterator LinkedList::find(const string& seek) const {
    for (Iterator i = begin(); i != end(); i++) {
        if (seek.compare(*i) == 0)
            return i;
    }

    return Iterator(tail);
}

int LinkedList::length() const {
    return len;
}

void LinkedList::clear() {
    if (length() == 0)
        return;

    Iterator i = begin();
    while (i != end()) {
        Iterator temp = i++;
        delete temp.ptr;
    }

    head->next = tail;
    tail->prev = head;

    len = 0;
}

LinkedList::Iterator LinkedList::begin() const {
    return Iterator(head->next);
}

LinkedList::Iterator LinkedList::end() const {
    return Iterator(tail);
}

LinkedList::Iterator::Iterator(Node* p) : ptr(p) { }

string& LinkedList::Iterator::operator*() {
    return ptr->data;
}

LinkedList::Iterator& LinkedList::Iterator::operator++() {
    ptr = ptr->next;
    return *this;
}

//Interesting that stack overflow says to always implement postincrement in terms of preincrement
LinkedList::Iterator LinkedList::Iterator::operator++(int) {
    Iterator result = *this;
    ++(*this);
    return result;
}

LinkedList::Iterator& LinkedList::Iterator::operator--() {
    ptr = ptr->prev;
    return *this;
}

LinkedList::Iterator LinkedList::Iterator::operator--(int) {
    Iterator result = *this;
    --(*this);
    return result;
}

bool LinkedList::Iterator::operator==(const Iterator& other) {
    return ptr == other.ptr;
}

bool LinkedList::Iterator::operator!=(const Iterator& other) {
    return ptr != other.ptr;
}