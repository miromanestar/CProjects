//  Name: Miro Manestar
//  Assignment number: 3
//  Assignment: Huffman Coding Tree
//  File name: huffman.cpp
//  Date last modified: October 14, 2020
//  Honor statement: I have neither given nor received any unauthorized help on this assignment. 

#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

class HuffmanNode {
    double freq;
public:
    HuffmanNode(double freq): freq(freq) { }
    double get_freq() { return freq; }
};

class Leaf: public HuffmanNode {
    char character;
public:
    Leaf(char ch, double freq): HuffmanNode(freq), character(ch) { }
};

class Branch: public HuffmanNode {
    HuffmanNode *left;
    HuffmanNode *right;
public:
    Branch(double freq, HuffmanNode *left, HuffmanNode *right):
        HuffmanNode(freq), left(left), right(right) { }
};

vector<int> get_freq() {
    vector<int> data(27);

    char character;
    while (cin.get(character)) {
        cout << character;

        if (isalpha(character)) {
            character = toupper(character);
            data[character - 65] += 1;
            
            data[26] += 1; //Total
        }
    }

    return data;
}

priority_queue<HuffmanNode *> make_queue(vector<int> v) {
    priority_queue<HuffmanNode *> queue;
    for (int i = 0; i < v.size() - 1; i++) {
        //Index represnts char, v[26] is the total
        queue.push(new Leaf(i + 65, v[i]/v[26]));
    }
}

int main() {
    //Using a vector allows each frequency update to be done
    //in constant time rather than log(n) in the case of a map
    //or n in the case of a queue
    vector<int> freqTable = get_freq();

    cout << "\nCounts:\n" << "-------\n";
    for (int i = 0; i < (int) freqTable.size() - 1; i++)
        cout << (char) ('A' + i) << ": " << freqTable[i] << '\n';
    cout << "Total: " << freqTable[26] << '\n';

    priority_queue<HuffmanNode *> queue = make_queue(freqTable);

    return 1;
}