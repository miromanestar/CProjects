#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {

    //What??? I like colored consoles....
    string red = "\u001b[31m";
    string green = "\u001b[32m";
    string yellow = "\u001b[33m";
    string blue = "\u001b[34m";
    string reset = "\u001b[0m";

    makePuzzle(20, 20);

    return 0;
}

string makePuzzle(int height, int width) {

    string puzzle[20][20]; 

    for(int i = 0; i < height; i++) {
        for(int j = 0; i < width; i++) {
            puzzle[i][j] = ".";
        }
    }

    return puzzle;
}