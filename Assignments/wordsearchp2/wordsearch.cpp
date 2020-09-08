#include <iostream>
#include <string>
#include <vector>
#include "wordsearch.h"

static char filler = ' ';
static std::vector<std::vector<int>> directions{{0, -1},  //Up
                                                {0, 1},   //Down
                                                {-1, 0},  //Left
                                                {0, -1},  //Right
                                                {-1, -1}, //Up-Left
                                                {1, 1},   //Down-Right
                                                {-1, 1},  //Down-Left
                                                {1, -1}}; //Up-Right
                                                
static std::vector<int> findWord(int x, int y, const std::string& word, LetterMatrix puz) {
    //If first letter doesn't match, move on (Saves time)
    if(puz[y][x] != word[0]) {
        return {-1};
    }

    int dx, dy;
    for(std::vector<int> direction : directions) {
        dx = direction[0];
        dy = direction[1];

        for(int i = 1; i < (int) word.size(); i++) {
            try {
                char temp = puz.at(y + (i * dy)).at(x + (i * dx));
                if(temp != word[i]) { 
                    break;
                } else if(i == (int) word.size() - 1) {
                    return {x, y, dx, dy};
                }
            } catch(const std::out_of_range& oor) {
                break;
            }
        }
    }
    return {-1};
}

static LetterMatrix fillSol(int x, int y, int dx, int dy, std::string word, LetterMatrix sol) {
    for(int i = 0; i < (int) word.size(); i++) {
            sol[y + (i * dy)][x + (i * dx)] = word[i];
    }
    return sol;
}

// Produces an answer key for a wordsearch puzzle given a
// puzzle and a list of words to find.
// puzzle: the word search puzzle to solve
// wordlist: the list of words to find within the puzzle
// Returns a new puzzle with the extraneous letters replaced
// with periods (.), revealing the locations of the words to find
LetterMatrix solve(const LetterMatrix& puzzle, const std::vector<std::string>& wordlist) {
    // Build an initial solution filled with periods
    LetterMatrix solution(puzzle.size(), std::vector<char>(puzzle[0].size(), filler));
     std::vector<int> pos;

    for(std::string word : wordlist) {
        for(int y = 0; y < (int) puzzle.size(); y++) {
            for(int x = 0; x < (int) puzzle[y].size(); x++) {
                pos = findWord(x, y, word, puzzle);
                if (pos[0] != -1) {
                    solution = fillSol(pos[0], pos[1], pos[2], pos[3], word, solution);
                }
            }
        }
    }
    return solution;
}


