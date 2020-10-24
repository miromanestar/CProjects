//  Name: Miro Manestar
//  Assignment number: 4
//  Assignment: Maze Generation
//  File name: maze.cpp
//  Date last modified: October 23, 2020
//  Honor statement: I have neither given nor received any unauthorized help on this assignment.

#include <iostream>
#include <vector>
#include <string>

using namespace std;

void gen_grid(int sizeX, int sizeY) {
    int count = 0;
    for (int i = 0; i < sizeY; i++) {
        for (int k = 0; k < sizeX; k++) {
            if (i % 2 == 0 || i == sizeY - 1)
                cout << " --";
            else {
                if (count < 10)
                    cout << "|" << count << " ";
                else
                    cout << "|" << count;
                count++;
            }
        }
        cout << endl;
    }
}

int main() {
    gen_grid(10, 10);
}