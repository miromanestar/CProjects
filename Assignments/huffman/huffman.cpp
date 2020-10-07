//  Name: Miro Manestar
//  Assignment number: 3
//  Assignment: Huffman Coding Tree
//  File name: huffman.cpp
//  Date last modified: October 7, 2020
//  Honor statement: I have neither given nor received any unauthorized help on this assignment. 

#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<char> huffVector(25);

void processChar(char character) {
    cout << character;

    if(!isalpha(character))
        return;
    
    character = toupper(character);
    huffVector[character - 65] += 1;
}

bool read_data() {
    char character;
    while (cin.get(character)) {
        processChar(character);
    }
    return true;
}

int main() {

    read_data();

    cout << "Counts:\n" << "-------\n";
    for(int i = 0; i < huffVector.size(); i++) {
        cout << 'A' + i << ": " << huffVector[i] << '\n';
    }
    cout << '\n';

}