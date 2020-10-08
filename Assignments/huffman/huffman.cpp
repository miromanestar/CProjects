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
void sort_counts();
void make_tree();
void sort_table();

vector<int> counts(26);
vector<vector<int>> freqTable;

//Small little class to store a linked-list for the huffman coding tree
class Tree {
    char letter;
    struct Node {
        Node *left, *right;
    };
    Node *first, *last;
};

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

    make_table();

    for(vector<int> val : freqTable) {
        cout << val[0] << ": " << val[1] << '\n';
    }
}

void make_table() {
    for(int i = 0; i < counts.size(); i++) {
        freqTable.push_back({i + 65, counts[i]});
    }

    sort_table();
}

void sort_table() {
    for(int i = 0; i < freqTable.size(); i++) {
        vector<int> min = freqTable[0];
        for(int k = i + 1; k < freqTable.size(); k++) {
            if(freqTable[k][1] < min[1]) {
                min = freqTable[k];
            }
        }
        vector<int> temp = freqTable[i];
        freqTable[i] = min;
        
    }
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