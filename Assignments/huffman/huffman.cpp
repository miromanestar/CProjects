//  Name: Miro Manestar
//  Assignment number: 3
//  Assignment: Huffman Coding Tree
//  File name: huffman.cpp
//  Date last modified: October 8, 2020
//  Honor statement: I have neither given nor received any unauthorized help on this assignment. 

#include <iostream>
#include <vector>
#include <string>

#include <fstream>

using namespace std;

//Node structure to contain the binary tree
struct Node {
    char letter;
    int freq;
    Node *left, *right;

    Node *next; //I feel like using the node itself for a FIFO structure is a bad idea but here we are...

    Node(char letter, int freq): letter(letter), freq(freq) { 
        this->next = nullptr;
        this->left = nullptr;
        this->right = nullptr;

    }
};

vector<int> get_freq();
vector<vector<int>> sort_freq(vector<int> v);
Node* make_tree(vector<vector<int>> sorted_freq);
void print_tree(Node* tree);

int main() {
    //Gets an unsorted frequency table of letters from stdin
    //Who needs maps anyway????
    vector<int> freqTable = get_freq();

    cout << "\nCounts:\n" << "-------\n";
    for (int i = 0; i < (int) freqTable.size() - 1; i++)
        cout << (char) ('A' + i) << ": " << freqTable[i] << '\n';
    cout << "Total: " << freqTable[26] << '\n';


    //Sorts the unsorted frequency table to a sorted frequency table
    //It's a 2D array because freqTable uses the index to store the character; i.e. index '0' is 'A', and it's value is the frequency A appeared
    //sorted_freqTable, since it isn't alphabetical but sorted by frequency, stores the character in a 2d array with its frequency.
    vector<vector<int>> sorted_freqTable = sort_freq(freqTable);

    /*
    //Print out sorted table for debugging
    for (int i = 0; i < (int) sorted_freqTable.size() - 1; i++)
        cout << (char) sorted_freqTable[i][0] << ": " << sorted_freqTable[i][1] << '\n';
    */

    Node* tree = make_tree(sorted_freqTable);

    cout << "\n------Huffman Coding Tree-------\n";
    print_tree(tree);
    cout << "\n--------------------------------\n";
}

Node* make_tree(vector<vector<int>> sorted_freq) {

    //Build the queue, starting with lowest frequency items
    Node *head;
    Node *p;
    for (int i = 0; i < (int) sorted_freq.size() - 1; i++) {
        Node *temp = new Node(sorted_freq[i][0], sorted_freq[i][1]);
        if (i == 0)
            head = temp;
        else
            p->next = temp;
        p = temp;
    }

    
    //Print out queue for debugging
    cout << '\n';
    for (Node *i = head; i != nullptr; i = i->next) {
        cout << i->letter << ": " << i->freq << '\n';
    }
    
    //Build the binary tree
    while (head->next != nullptr) {
        Node *temp = new Node('.', head->freq + head->next->freq);
        temp->left = head;
        temp->right = head->next;

        Node *prev;
        for (Node *i = head; i != nullptr; i = i->next) {
            if (temp->freq < i->freq) {
                temp->next = i;
                prev->next = temp;
                break;
            }
            prev = i;
        }

        head = head->next->next;
    }

    return head;
}

void print_tree(Node* tree) {
    cout << '\n';
    while (tree->right != nullptr) {
        cout << tree->left->letter << ": " << tree->left->freq << '\t';

        if (tree->right->letter != ' ')
            cout << tree->right->letter << ": " << tree->right->freq;
        cout << '\n';
        tree = tree->right;
    }
}


//Reads in data and reads the frequencies of alphabetic characters only
vector<int> get_freq() {
    vector<int> data(27);

    //ifstream input;
    //input.open("declaration.txt");

    char character;
    while (cin.get(character)) {
        cout << character;

        if (isalpha(character)) {
            character = toupper(character);
            data[character - 65] += 1;

            data[26] += 1;
        }
            
    }

    return data;
}

/*
    This... mess of code takes an input vector v and transforms it into a sorted vector of vectors of ints.
    It essentially goes through vector v, finds the min, assigns min to { index, value }, where index is actually
    used to represent a character... i.e. index '0' represents 'A'. Meanwhile, value represents the number of times
    that character appeared in a string. Next, it marks that index as "used" by assign v[index] to a value of -1.
    Finally, it pushes the min to the sorted vector.
*/
vector<vector<int>> sort_freq(vector<int> v) {
    vector<vector<int>> sorted;

    for (int i = 0; i < (int) v.size(); i++) {

        //Set min to whatever value of i we're at... the first part is just filler
        //The +65 is because the char 'A' is represented by 65 in ASCII
        vector<int> min = { i + 65, v[i] };
        for (int k = 0; k < (int) v.size(); k++) {

            //If v[k] is -1, it means that slot has already been sorted into the new vector and should be ignored
            if (v[k] != -1 && min[1] >= v[k])
                min = { k + 65, v[k] };
            //Sometimes, min is set to -1, so this sets min to something other than -1 if the current traversed value is not -1
            else if (min[1] == -1 && v[k] != -1)
                min = { k + 65, v[k] };
        }
        v[min[0] - 65] = -1;
        sorted.push_back(min);
    }

    return sorted;
}