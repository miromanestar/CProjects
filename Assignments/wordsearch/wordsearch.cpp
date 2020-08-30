#include "uniformrandom.h"
#include "wordsearch.h"
#include <stdlib.h>
#include <time.h>
#include <vector>

static LetterMatrix puzzle;
static char filler = ' ';

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
    for (int i = 0; i < word.size(); i++) {
        try {
            char tempValue = puzzle.at(y + (i * dy)).at(i + (x * dx));
            if(!tempValue && tempValue != filler || tempValue == (char) word[i]) {
                return false;
            }
        } catch(const std::out_of_range& oor) {
            return false;
        }
    }

    return true;
}

static void placeWord(std::string word, int rows, int columns) {
    //Choose initial x/y positions
    int x = rand() % rows;
    int y = rand() % columns;

    //Choose a direction in a dx,dy format
    std::vector<std::vector<int>> directions{{1, 0}, //Right
                                             {0, 1}, //Down
                                             {1, 1}, //Right-Down
                                             {0, -1}, //Up
                                             {-1, 0}, //Right
                                             {-1, -1}}; //Up-Right

    int dx, dy;
    try{ 
        std::vector<int> choice = directions[rand() % directions.size() - 1];
        dx = choice.at(0); dy = choice.at(1);
    //I couldn't figure out how to fix these but I think I "handled" it"
    } catch(const std::out_of_range& e) {
        //std::cout << "Error: " << e.what() << '\n';

    } catch(const std::bad_alloc& e) {
        //std::cout << "Error: " << e.what() << '\n';
    }

    if(checkDirection(x, y, dx, dy, word)) {
        for (int i = 0; i < word.size(); i++) {
            //If this ever causes a segmentation fault, the problem is in checkDirection()
            puzzle[y + (i * dy)][i + (x * dx)] = word[i];
        }
    } else {
        placeWord(word, rows, columns);
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
        placeWord(word, rows, columns);
    }

    return puzzle;
}


//  Constructs a puzzle from a given key.
//  key: the key from which the puzzle is to be created.
//  Returns the newly created corresponding word search puzzle.
LetterMatrix make_puzzle(const LetterMatrix& key) {
    auto r = UniformRandomGenerator(65, 90);
    LetterMatrix finishedPuzzle(key.size(), std::vector<char>(key[0].size(), filler));

    for (int i = 0; i < key.size(); i++) {
        for (int j = 0; j < key.size(); j++) {
            if(key[i][j] == filler) {
                finishedPuzzle[i][j] = r();
            } else {
                finishedPuzzle[i][j] = key[i][j];
            }
        }
    }

    return finishedPuzzle;
}
