//  File simplevectortestfile.cpp

#include <iostream>
#include "vectorutils.h"

//  This code performs *extremely* simple
//  tests.  This is only the first steps to any
//  testing you may want to perform.  You must ensure
//  that your vectorstuff.cpp file compiles cleanly
//  with this file.  If the compiler generates errors
//  when using your code and this code together, your
//  code has no chance passing my more extensive test
//  suite.
//
//  Since this is only a very test simple suite, you should
//  create more interesting tests in an attempt to reveal
//  the logic errors that may be lurking in your
//  functions.

// Conveniently print the contents of a vector.
template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &vec)
{
    os << '{';
    if (!vec.empty())
    {
        auto iter = vec.begin();
        auto end = vec.end();
        os << *iter++;
        while (iter != end)
            os << ", " << *iter++;
    }
    os << '}';
    return os;
}

int main()
{
    //  Make a small vector of integers
    std::vector<int> list{1, 5, 3, 10, 3, 7, 5, 2};
    std::vector<int> list1{1, 2, 3, 4, 5, 5, 4, 3, 2, 1, 1};
    std::vector<int> list2{1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 1};
    std::vector<int> list3{};
    std::vector<int> list4{99};

    //  Some variables to ensure the function return types
    //  are properly assignable.
    int i;
    bool b;

    i = maximum(list);
    std::cout << "The largest in " << list << " is " << i << '\n';

    i = maximum(list1);
    std::cout << "The largest in " << list1 << " is " << i << '\n';

    i = maximum(list2);
    std::cout << "The largest in " << list2 << " is " << i << '\n';

    std::cout << "---------------------------------\n";

    i = find(list, 10);
    std::cout << "10 is at index " << i << " in " << list << '\n';

    i = find(list2, 10);
    std::cout << "10 is at index " << i << " in " << list2 << '\n';

    i = find(list2, 3);
    std::cout << "3 is at index " << i << " in " << list2 << '\n';

    i = find(list2, 1);
    std::cout << "1 is at index " << i << " in " << list2 << '\n';
    std::cout << "---------------------------------\n";

    i = count(list, 3);
    std::cout << "3 occurs " << i << " times in " << list << '\n';

    i = count(list, 8);
    std::cout << "8 occurs " << i << " times in " << list << '\n';

    i = count(list, 1);
    std::cout << "1 occurs " << i << " times in " << list << '\n';

    i = count(list, 5);
    std::cout << "5 occurs " << i << " times in " << list << '\n';

    i = count(list, 10);
    std::cout << "10 occurs " << i << " times in " << list << '\n';

    i = count(list1, 1);
    std::cout << "1 occurs " << i << " times in " << list1 << '\n';

    std::cout << "---------------------------------\n";

    b = equivalent(list1, list2);
    if (b)
    {
        std::cout << list1 << " is equivalent to " << list2 << '\n';
    }
    else
    {
        std::cout << list1 << " is not equivalent to " << list2 << '\n';
    }

    b = equivalent(list3, list3);
    if (b)
    {
        std::cout << list3 << " is equivalent to " << list3 << '\n';
    }
    else
    {
        std::cout << list3 << " is not equivalent to " << list3 << '\n';
    }

    b = equivalent(list3, list4);
    if (b)
    {
        std::cout << list3 << " is equivalent to " << list4 << '\n';
    }
    else
    {
        std::cout << list3 << " is not equivalent to " << list4 << '\n';
    }
    std::cout << "---------------------------------\n";


    std::vector<int> testList{ 2,2,2,3,3 };
    std::vector<int> testList2{ 2,2,3,3,3 };

    b = equivalent(testList, testList2);
    if (b) {
        std::cout << testList << " is equivalent to " << testList2 << '\n';
    } else {
        std::cout << testList << " is not equivalent to " << testList2 << '\n';
    }

    b = equivalent(testList2, testList);
    if (b) {
        std::cout << testList2 << " is equivalent to " << testList << '\n';
    } else {
        std::cout << testList2 << " is not equivalent to " << testList << '\n';
    }

    // list = { 1,2,3,4,5 };
    // list = { 5,4,3,2,1 };
    list = {1, 3, 5, 7, 2, 9, 6, 8, 9, 9};
    sort(list);
    std::cout << list << " sorted" << '\n';
    sort(list3);
    std::cout << list3 << " sorted" << '\n';
    std::cout << "---------------------------------\n";

    list = {1, 5, 3, 10, 3, 7, 5, 2};
    // list = { 1, 5, 3, 3, 10, 3, 7, 5, 2 };
    // list = { 3, 5, 3, 10, 3, 7, 5, 2 };
    // list = { 1, 5, 10, 7, 5, 2 , 3};
    // list = { 1, 5, 10, 7, 5, 2};
    std::cout << "Before: " << list << '\n';
    b = remove_first(list, 3);
    if (b)
    {
        std::cout << "returned true" << '\n';
    }
    else
    {
        std::cout << "returned false" << '\n';
    }
    std::cout << "After removing the first 3: " << list << '\n';

    std::cout << "Before: " << list4 << '\n';
    b = remove_first(list4, 99);
    if (b)
    {
        std::cout << "returned true" << '\n';
    }
    else
    {
        std::cout << "returned false" << '\n';
    }
    std::cout << "After removing the first 99: " << list4 << '\n';
    std::cout << "---------------------------------\n";
}
