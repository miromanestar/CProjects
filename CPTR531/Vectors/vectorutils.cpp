//  Name: Miro Manestar
//  Assignment number: 1
//  Assignment: C++ Vector Algorithms
//  File name: vectorutils.cpp
//  Date last modified: August 25, 2022
//  Honor statement: I have neither given nor received any unauthorized help on this assignment. 

#include "vectorutils.h"

using namespace std;

int maximum(const vector<int>& v) {
    int max = v[0];

    for (int i = 1; i < v.size(); i++) {
        if (v[i] > max)
            max = v[i];
    }

    return max;
}

int find(const vector<int>& v, int seek) {
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == seek)
            return i;
    }

    return -1;
}

int count(const vector<int>& v, int seek) {
    int count = 0;

    for (int i = 0; i < v.size(); i++) {
        if (v[i] == seek)
            count++;
    }

    return count;
}

bool equivalent(const vector<int>& v1, const vector<int>& v2) {
    if (v1.size() != v2.size())
        return false;

    for (int i = 0; i < v1.size(); i++) {
        if (find(v2, v1[i]) == -1)
            return false;

        if (count(v1, v1[i]) != count(v2, v1[i]))
            return false;
    }

    return true;
}

void sort(vector<int>& v) {
    for (int i = 1; i < v.size(); i++) {
        int j = i;
        while (j > 0 && v[j] < v[j - 1]) {
            int temp = v[j];
            v[j] = v[j - 1];
            v[j - 1] = temp;
            j--;
        }
    }
}

bool remove_first(vector<int>& v, int del) {
    int pos = find(v, del);

    if (pos == -1)
        return false;

    for (int i = pos; i < v.size() - 1; i++) {
        v[i] = v[i + 1];
    }

    v.pop_back();
    return true;
}