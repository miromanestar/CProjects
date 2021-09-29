// listmain.cpp

#include <iostream>
#include <algorithm>
#include "llist.h"

#include <vector>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../Doctest/doctest.h"

using std::vector;
using std::string;

// I would make LinkedList take an initializer list, but we can't modify llist.h
LinkedList ll(vector<string> vec) {
    LinkedList list;
    for (string s : vec) list.insert(list.end(), s);
    return list;
}

std::ostream& operator<< (std::ostream& os, const LinkedList& list) {
    os << "[";
    if (list.length() > 0) os << *(list.begin());
    for (auto i = ++list.begin(); i != list.end(); i++) {
        os << ", " << *i;
    }
    os << "]";
    return os;
}


TEST_CASE("Construction/Assignment") {
    LinkedList listA;
    CHECK(listA.length() == 0);
    
    LinkedList listB = ll({"A", "B", "C"});
    CHECK(listB.length() == 3);

    LinkedList listC = listB; // copy
    CHECK(listC == listB);
    CHECK(listC.begin() != listB.begin());
    CHECK((listC.begin()++) != (listB.begin()++));

    listA = listB; // Assignment
    CHECK(listA == listB);
    CHECK(listC.begin() != listB.begin());
    CHECK((listC.begin()++) != (listB.begin()++));

    listA = listA; // self assignment
    CHECK(listA.length() == 3);
}

TEST_CASE("Equality") {
    LinkedList empty1, empty2,
               list1 = ll({"A", "B", "C"}), list2 = ll({"A", "B"}),
               list3 = ll({"C", "B", "A"}), list4 = ll({"A", "B", "C"});

    SUBCASE("Lists") {
        CHECK(empty1 == empty2);
        CHECK(empty1 != list1);
        CHECK(list1 != list2);
        CHECK(list1 != list3);
        CHECK(list1 == list4);
    }

    SUBCASE("Iterators") {
        CHECK(empty1.end() == empty1.end());
        CHECK(empty1.begin() != empty2.begin());
        CHECK(++list2.begin() == --list2.end());
        CHECK(++list2.begin() != ++list4.begin());
    }
}

TEST_CASE("Iteration") {
    LinkedList list = ll({"Fred", "Wilma", "Betty", "Dino", "Barney"});

    SUBCASE("Iterators") {
        CHECK(*(list.begin()) == "Fred");
        CHECK(*(--list.end()) == "Barney");
        CHECK(*(++list.begin()) == "Wilma");

        auto it = list.begin();
        CHECK(*(it++) == "Fred");
        CHECK(*(it) == "Wilma");

        it = --list.end();
        CHECK(*(it--) == "Barney");
        CHECK(*(it) == "Dino");
    }

    SUBCASE("for each loop") {
        vector<string> vec{};
        for (string elem : list) {
            vec.push_back(elem);
        }
        CHECK(vec == vector<string>{"Fred", "Wilma", "Betty", "Dino", "Barney"});
    }

    SUBCASE("std::for_each") {
        vector<string> vec{};
        std::for_each(list.begin(), list.end(), [&](string s) { vec.push_back(s); });
        CHECK(vec == vector<string>{"Fred", "Wilma", "Betty", "Dino", "Barney"});
    }
}

TEST_CASE("Modification") {
    LinkedList list;
    REQUIRE(list.length() == 0);

    list.insert(list.end(), "A");
    list.insert(list.end(), "B");
    list.insert(list.end(), "C");
    REQUIRE(list == ll({"A", "B", "C"}));

    SUBCASE("insert") {
        list.insert(list.begin(), "NEW");
        CHECK(list == ll({"NEW", "A", "B", "C"}));
    }
    SUBCASE("insert middle") {
        list.insert(++list.begin(), "NEW");
        CHECK(list == ll({"A",  "NEW", "B", "C"}));
    }

    SUBCASE("remove begin") {
        auto it = list.begin();
        list.remove(it);
        CHECK(list == ll({"B", "C"}));
        CHECK(*it == "B");
    }
    SUBCASE("remove end") {
        auto it = --list.end();
        list.remove(it);
        CHECK(list == ll({"A", "B"}));
        CHECK(it == list.end());
    }
    SUBCASE("remove middle") {
        auto it = ++list.begin();
        list.remove(it);
        CHECK(list == ll({"A", "C"}));
        CHECK(*it == "C");
    }

    SUBCASE("clear") {
        list.clear();
        CHECK(list.length() == 0);
        list.insert(list.end(), "A");
        CHECK(list.length() == 1);
        
        LinkedList empty;
        empty.clear();
        CHECK(empty.length() == 0);
    }
}

TEST_CASE("Find") {
    LinkedList list = ll({"A", "B", "C"});

    CHECK(list.find("A") == list.begin());
    CHECK(list.find("B") == ++list.begin());
    CHECK(list.find("C") == --list.end());
}