#include <iostream>
#include <vector>
#include <string>

using namespace std;

//What??? I like colored consoles....
string red = "\u001b[31m";
string green = "\u001b[32m";
string yellow = "\u001b[33m";
string blue = "\u001b[34m";
string reset = "\u001b[0m";

vector<vector<string>> puzzle(20, vector<string>(20));

//Function definitions because I like keeping main on top
void makePuzzle();
void printPuzzle();

int main() {
    makePuzzle();
    return 0;
}

void makePuzzle() {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            puzzle[i][j] = ".";
        }
    }
}

void printPuzzle() {
    
}