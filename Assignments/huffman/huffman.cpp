//  Name: Miro Manestar
//  Assignment number: 3
//  Assignment: Huffman Coding Tree
//  File name: huffman.cpp
//  Date last modified: October 20, 2020
//  Honor statement: I have neither given nor received any unauthorized help on this assignment. 

#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

class HuffmanNode {
protected:
    double freq;

public:
    HuffmanNode(double freq): freq(freq) { }
    double get_freq() { return freq; }
    
    virtual void print_prefixes(string prefix) const = 0;
    virtual void print_prefixes() const { print_prefixes(""); }

    virtual void print_tree(int depth, char link) const = 0;
    virtual void print_tree() const { print_tree(0, '-'); }
};

class Leaf: public HuffmanNode {
    char character;

public:
    Leaf(char ch, double freq): HuffmanNode(freq), character(ch) { }

    void print_prefixes(string bitString) const override {
        cout << character << " : " << bitString << endl;
    }

    void print_tree(int depth, char link) const override {
        for (int i = 0; i < depth; i++)
            cout << "    ";
        cout << link << '[' << character << ": " << freq << ']' << endl;
    }
};

class Branch: public HuffmanNode {
    HuffmanNode *left;
    HuffmanNode *right;

public:
    Branch(double freq, HuffmanNode *left, HuffmanNode *right):
        HuffmanNode(freq), left(left), right(right) { }

    void print_prefixes(string bitString) const override {
        if (left != nullptr)
            left->print_prefixes(bitString + "0");
        if (right != nullptr)
            right->print_prefixes(bitString + "1");
    }

    void print_tree(int depth, char link) const override {
        if (right != nullptr)
            right->print_tree(depth + 1, '/');
        
        for (int i = 0; i < depth; i++)
            cout << "    ";
        cout << link << '[' << freq << ']' << endl;

        if (left != nullptr)
            left->print_tree(depth + 1, '\\');
    }

};

struct CompareFreq {
    bool operator() (HuffmanNode *n1, HuffmanNode *n2) {
        return n1->get_freq() > n2->get_freq();
    }
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

HuffmanNode* make_tree(vector<int> v) {
    //Build the queue
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareFreq> queue;
    //size - 1 for v because last index of v holds the total
    for (int i = 0; i < (int) v.size() - 1; i++)
        queue.push(new Leaf(i + 65, (float) v[i]/v[26]));

    //Make the tree
    while (queue.size() > 1) {
        HuffmanNode *n1 = queue.top();
        queue.pop();
        HuffmanNode *n2 = queue.top();
        queue.pop();

        queue.push(new Branch(n1->get_freq() + n2->get_freq(), n1, n2));
    }

    return queue.top();
}

int main() {
    //Using a vector allows each frequency update to be done
    //in constant time rather than log(n) in the case of a map
    //or n in the case of a queue
    vector<int> freqTable = get_freq();

    cout << "\nCounts:\n" << "-------\n";
    for (int i = 0; i < (int) freqTable.size() - 1; i++)
        cout << (char) ('A' + i) << ": " << freqTable[i] << endl;
    cout << "Total: " << freqTable[26] << endl;

    HuffmanNode *tree = make_tree(freqTable);
    cout << "\n------Huffman Coding Tree-------\n\n";
    tree->print_tree();
    cout << "\n--------------------------------\n";
    tree->print_prefixes();
}