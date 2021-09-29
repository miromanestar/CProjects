//  Name:           Logan Bateman
//  Description     doctests for assignment A2
//  Class:          CPTR-571 (System Software and Architecture)
//  File name:      tests.cpp
//  Last Modified:  Sep 26, 2021

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../Doctest/doctest.h"

#include "llist.h"

LinkedList *new_testlist() {
    LinkedList *testlist = new LinkedList();
    testlist->insert(testlist->end(), "Testing");
    testlist->insert(testlist->end(), "Testing2");
    testlist->insert(testlist->end(), "Testing3");
    testlist->insert(testlist->end(), "Testing4");
    return testlist;
}

LinkedList testlist() {
    LinkedList testlist;
    testlist.insert(testlist.end(), "Testing");
    testlist.insert(testlist.end(), "Testing2");
    testlist.insert(testlist.end(), "Testing3");
    testlist.insert(testlist.end(), "Testing4");
    return testlist;
}

TEST_CASE("Testing contruct/destruct") {
    LinkedList testlist;
    CHECK(testlist.length() == 0);
    CHECK(true);
}

TEST_CASE("Standard insertion at end()") {
    auto list = testlist();
    auto iter = list.begin();
    CHECK(*iter == "Testing");
    CHECK(*(++iter) == "Testing2");
    CHECK(list.length() == 4);
}

TEST_CASE("Standard insertion at end()") {
    auto list = testlist();
    list.insert(list.begin(), "Testing0");
    auto iter = list.begin();
    CHECK(*iter == "Testing0");
    CHECK(*(++iter) == "Testing");
    CHECK(list.length() == 5);
}

TEST_CASE("Middle insertion") {
    auto list = testlist();
    // Insert in middle
    list.insert(list.find("Testing3"), "Testing2.5");
    CHECK(list.length() == 5);
    CHECK(*(--list.find("Testing2.5")) == "Testing2");
    CHECK(*(++list.find("Testing2.5")) == "Testing3");
}

TEST_CASE("Beginning sentinel insertion") {
    auto list = testlist();
    // Insertion before beginning (assume not inserted)
    // Nothing should be inserted before beginning sentinel
    int oldlen = list.length();
    list.insert(--list.begin(), "Before beginning");
    CHECK(list.find("Before beginning") == list.end());
    CHECK(list.length() == oldlen);
}

TEST_CASE("Find") {
    auto list = testlist();
    CHECK(list.find("Testing") == list.begin());
    CHECK(*list.find("Testing2") == "Testing2");
    CHECK(++list.find("Testing4") == list.end());
    CHECK(list.find("") == list.end());
    CHECK(list.find("Test") == list.end());
}

TEST_CASE("Find/Deletion") {
    auto list = testlist();
    auto iter = list.find("Testing3");
    CHECK(*iter == "Testing3");
    CHECK(list.length() == 4);
    list.remove(iter);
    CHECK(list.find("Testing3") == list.end());
    CHECK(list.length() == 3);

}

TEST_CASE("Delete front or end sentinel") {
    auto list = testlist();
    CHECK(*(--list.begin()) == "*HEAD*");
    CHECK(list.find("*TAIL*") == list.end());
    // Remove beginning or end
    auto iterbegin = list.begin();
    auto iterend = list.end();
    list.remove(--iterbegin);
    list.remove(iterend);
    CHECK(list.length() == 4);
    CHECK(*(--list.begin()) == "*HEAD*");
    CHECK(list.find("*TAIL*") == list.end());
}

TEST_CASE("Clear") {
    auto list = testlist();
    CHECK(list.length() == 4);
    list.clear();
    CHECK(list.length() == 0);
}

TEST_CASE("List equality/inequality") {
    auto list1 = testlist();
    auto list2 = testlist();
    CHECK(list1 == list2);
    list1.insert(list1.begin(), "New begin");
    CHECK(list1 != list2);
}

TEST_CASE("Iterator inc/dec") {
    auto list = testlist();
    auto iter = list.begin();
    CHECK(*iter == "Testing");
    CHECK(*(iter++) == "Testing");
    CHECK(*iter == "Testing2");
    CHECK(*(++iter) == "Testing3");
    CHECK(*iter == "Testing3");
    CHECK(*(iter--) == "Testing3");
    CHECK(*iter == "Testing2");
    CHECK(*(--iter) == "Testing");
    // Unsupported
    // iter += 2;
    // CHECK(*iter == "Testing3");
}

TEST_CASE("Iterator equivalence") {
    auto list = testlist();
    CHECK(list.begin() != list.end());
    list.clear();
    CHECK(list.begin() == list.end());
}

TEST_CASE("Copy list") {
    auto list1 = testlist();
    auto list2 = list1;
    CHECK(list1 == list2);
    CHECK(list1.begin() != list2.begin());
}

TEST_CASE("Reassign list - heap") {
    auto *list1 = new_testlist();
    list1->insert(list1->end(), "Testing5");
    auto *list2 = new_testlist();
    auto head2 = --list2->begin();
    auto begin2 = list2->begin();
    auto *list3 = new_testlist();
    CHECK(*list1 != *list2); // different content
    // Assignment - if done improperly, should cause a leak
    *list2 = *list1;
    *list3 = *list1;
    CHECK(*list1 == *list2); // content got copied
    CHECK(list1->begin() != list2->begin()); // not a bit for bit copy
    CHECK(list2->begin() != begin2); // not the same
    CHECK(--list2->begin() == head2); // Heads match (during assignment, head/tail did not get replaced)
    delete list1;
    delete list2;
    delete list3;
}

TEST_CASE("Reassign list - stack") {
    auto list1 = testlist();
    list1.insert(list1.end(), "Testing5");
    auto list2 = testlist();
    auto head2 = --list2.begin();
    auto begin2 = list2.begin();
    auto list3 = testlist();
    CHECK(list1 != list2); // different content
    // Assignment - if done improperly, should cause a leak
    list2 = list1;
    list3 = list1;
    CHECK(list1 == list2); // content got copied
    CHECK(list1.begin() != list2.begin());
    CHECK(list2.begin() != begin2);
    CHECK(--list2.begin() == head2); // Heads match (during assignment, head/tail did not get replaced)
}