//  Name: Miro Manestar
//  Assignment number: 4
//  Assignment: Maxe Generation
//  File name: maze.cpp
//  Date last modified: October 23, 2020
//  Honor statement: I have neither given nor received any unauthorized help on this assignment.

#include <iostream>
#include <vector>
#include <string>

using namespace std;

void gen_grid(int sizeX, int sizeY) {
    for (int i = 0; i < sizeX; i++) {
        for (int k = 0; k < sizeY; k++) {
            if (k % 2 == 0)
                cout << " | ";
            else
                cout << " -- ";
        }
        cout << endl;
    }
}

int main() {
    gen_grid(10, 10);
}