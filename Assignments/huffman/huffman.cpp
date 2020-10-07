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

void process_char(char character);
void read_data();
void make_tree();

vector<int> counts(26);

int main() {
    read_data();

    cout << "\nCounts:\n" << "-------\n";
    int total = 0;
    for(int i = 0; i < counts.size(); i++) {
        cout << (char) ('A' + i) << ": " << (int) (counts[i]) << '\n';
        total += counts[i];
    }
    cout << "Total = " << total << '\n';

    cout << "\n------Huffman Coding Tree-------\n";
    make_tree();
    cout << "\n--------------------------------\n";

}

void make_tree() {

}

void read_data() {
    char character;
    while (cin.get(character)) {
        process_char(character);
    }
}

void process_char(char character) {
    cout << character;

    if(!isalpha(character))
        return;
    
    character = toupper(character);
    counts[character - 65] += 1;
}