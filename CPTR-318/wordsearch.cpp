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

vector<vector<string>> puzzle;

//Function definitions
void makePuzzle();

int main() {

    makePuzzle();
    cout << "ddf";
    return 0;
}

void makePuzzle() {

    for(int i = 0; i < puzzle.size(); i++) {
        for(int j = 0; i < puzzle[i].size(); i++) {

            puzzle[i][j] = ".";
            cout << ".";
        }
        cout << "\n";
    }

    return;
}