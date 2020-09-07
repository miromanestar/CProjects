//Miro Manestar | CPTR-318 Wordserach Assignment Part 1
//Wednesday, September 2, 2020 

#include "uniformrandom.h"
#include "wordsearch.h"
#include <time.h>

static LetterMatrix puzzle;
static char filler = '.';
static std::vector<std::vector<int>> directions{{0, -1},  //Up
                                                {0, 1},   //Down
                                                {-1, 0},  //Left
                                                {0, -1},  //Right
                                                {-1, -1}, //Up-Left
                                                {1, 1},   //Down-Right
                                                {-1, 1},  //Down-Left
                                                {1, -1}}; //Up-Right

//-------------------------------------------------------
//  You may add any helper functions you desire.
//  If you do add your own any helper functions, declare them 
//  "static" so they will be local to this source file.
//-------------------------------------------------------

static void fillVector(int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        puzzle.push_back(std::vector<char>{});
        for (int j = 0; j < columns; j++) {
            puzzle[i].push_back(filler);
        }
    }
}

static bool checkDirection(int x, int y, int dx, int dy, std::string word) {
    for (int i = 0; i < (int) word.size(); i++) {
        try {
            char tempValue = puzzle.at(y + (i * dy)).at(x + (i * dx));
            if(tempValue != (char) word[i] && tempValue != filler) {
                return false;
            }
        } catch(const std::out_of_range& oor) {
            return false; //If word goes beyond wordsearch size, return false
        }
    }

    return true;
}

static void placeWord(std::string word, int rows, int columns, int iteration) {
    //Halts function if attempt to find a spot for a word has failed 30 times to stop infinite recursion
    if(iteration > 30) {
        return;
    }

    //Choose initial x/y positions
    int x = rand() % rows;
    int y = rand() % columns;

    int dx, dy;
    std::vector<int> choice = directions[rand() % directions.size()];
    dx = choice.at(0); dy = choice.at(1);

    if(checkDirection(x, y, dx, dy, word)) {
        for (int i = 0; i < (int) word.size(); i++) {
            //If this ever causes a segmentation fault, the problem is in checkDirection() bc it didn't correctly detect out of bounds error
            puzzle[y + (i * dy)][x + (i * dx)] = word[i];
        }
    } else {
        placeWord(word, rows, columns, iteration + 1);
    }
}

//  Constructs a puzzle key from a word list.
//  word_list: the vector of words to put into the puzzle.
//  rows: the number of rows in the puzzle
//  columns: the number of columns in the puzzle
//  Returns the newly created wordsearch puzzle key.
//  Note: The method"s behavior is undefined if all the words 
//  in its list cannot be placed.
LetterMatrix make_key(const std::vector<std::string>& word_list, int rows, int columns) {
    fillVector(rows, columns);
    srand(time(NULL));

    for (std::string word: word_list) {
        placeWord(word, rows, columns, 0);
    }

    return puzzle;
}


//  Constructs a puzzle from a given key.
//  key: the key from which the puzzle is to be created.
//  Returns the newly created corresponding word search puzzle.
LetterMatrix make_puzzle(const LetterMatrix& key) {
    auto r = UniformRandomGenerator(65, 90);
    LetterMatrix finishedPuzzle(key.size(), std::vector<char>(key[0].size(), filler));

    for (int i = 0; i < (int) key.size(); i++) {
        for (int j = 0; j < (int) key.size(); j++) {
            if(key[i][j] == filler) {
                finishedPuzzle[i][j] = r();
            } else {
                finishedPuzzle[i][j] = key[i][j];
            }
        }
    }

    return finishedPuzzle;
}

static std::vector<int> findWord(int x, int y, const std::string& word, LetterMatrix puz) {
    if(puz[y][x] != word[0]) {
        return {-1};
    }
    int dx, dy;
    for(int i = 0; i < (int) directions.size(); i++) {
        dx = directions[i][0];
        dy = directions[i][1];

        for(int i = 1; i < (int) word.size(); i++) {
            try {
                char tempValue = puz.at(y + (i * dy)).at(x + (i * dx));
                if(tempValue != word[i]) {
                    continue;
                }
                if(i == (int) directions.size() - 1 && tempValue != word[i]) {
                    return {-1};
                } else {
                    return {x, y, dx, dy};
                }
            } catch(const std::out_of_range& oor) {
                continue;
            }
        }
    }
    return {-1}; //This should never happen
}

static LetterMatrix fillSol(int x, int y, int dx, int dy, std::string word, LetterMatrix sol) {
    for(int i = 0; i < (int) word.size(); i++) {
            sol[y + (i * dy)][x + (i * dx)] = word[i];
    }
    return sol;
}

//Searches for items from wordlist inside puzzle
LetterMatrix solve(const LetterMatrix& puz, const std::vector<std::string>& wordlist) {
    LetterMatrix sol(puz.size(), std::vector<char>(puz[0].size(), filler));
    std::vector<int> pos;

    for(std::string word : wordlist) {
        for(int y = 0; y < (int) puz.size(); y++) {
            for(int x = 0; x < (int) puz[y].size(); x++) {
                pos = findWord(x, y, word, puz);
                if (pos[0] != -1) {
                    fillSol(pos[0], pos[1], pos[2], pos[3], word, sol);
                } else {
                    continue;
                }
            }
        }
    }
    return sol;
}
