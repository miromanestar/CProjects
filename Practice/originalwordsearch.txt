#include "uniformrandom.h"
#include "wordsearch.h"
#include <algorithm>

//-------------------------------------------------------
//  You may add any helper functions you desire.
//  If you do add your own any helper functions, declare them 
//  "static" so they will be local to this source file.
//-------------------------------------------------------

static bool checkDirection(std::string dir, int x, int y, std::string word);
static void choosePos(std::string word, int rows, int columns);
static void fillVector(int rows, int columns);

static LetterMatrix puzzle;
static char filler = '.';

//  Constructs a puzzle key from a word list.
//  word_list: the vector of words to put into the puzzle.
//  rows: the number of rows in the puzzle
//  columns: the number of columns in the puzzle
//  Returns the newly created wordsearch puzzle key.
//  Note: The method"s behavior is undefined if all the words 
//  in its list cannot be placed.
LetterMatrix make_key(const std::vector<std::string>& word_list, int rows, int columns) {
    fillVector(rows, columns);

    for (std::string word: word_list) {
        choosePos(word, rows, columns);
    }

    return {{'A', 'B', 'C', 'D'},
            {'E', 'F', 'G', 'H'},
            {'I', 'J', 'K', 'L'},
            {'M', 'N', 'O', 'P'}};
}


//  Constructs a puzzle from a given key.
//  key: the key from which the puzzle is to be created.
//  Returns the newly created corresponding word search puzzle.
LetterMatrix make_puzzle(const LetterMatrix& key) {
    //  Replace this statement with your code
    return key;
}

static void choosePos(std::string word, int rows, int columns) {
    int max = 0; 
    if (rows > columns) { max = rows; } else { max = columns; }
    auto r = UniformRandomGenerator(0, max);
    int x = r();
    int y = r();

    /*
        Checks in each of the four cardinal directions and pushes the direction to a vector if true...
        Also adds the four in-between directions if the vector contains two adjacent pairs and adds those to the vector
        This is an incredibly lazy solution I think and I"m kinda ashamed...
    */
    std::vector<std::string> directions;
    int length = word.length();
    if (length <= y)           { directions.push_back("u"); } //Up
    if (length <= rows - y)    { directions.push_back("d"); } //Down
    if (length <= x)           { directions.push_back("l"); } //Left
    if (length <= columns - x) { directions.push_back("r"); } //Right

    //Honestly... this part looks cancerous to me but I"m not sure how else to do it at the moment w/o a total rewrite...
    if(std::any_of(directions.begin(), directions.end(), "u") &&
       std::any_of(directions.begin(), directions.end(), "l")) { //Up-Left
        directions.push_back("ul");
    }
    if(std::any_of(directions.begin(), directions.end(), "u") &&
       std::any_of(directions.begin(), directions.end(), "r")) { //Up-Right
        directions.push_back("ur");
    }
    if(std::any_of(directions.begin(), directions.end(), "d") &&
       std::any_of(directions.begin(), directions.end(), "r")) { //Down-Right
        directions.push_back("dr");
    }
    if(std::any_of(directions.begin(), directions.end(), "d") &&
       std::any_of(directions.begin(), directions.end(), "l")) { //Down-Left
        directions.push_back("dl");
    }

    //Randomly pick one of the available directions!
    r = UniformRandomGenerator(0, directions.size() - 1);
    std::string chosenDir = directions[r()];
    if(checkDirection(chosenDir, x, y, word)) {

    }
}

static bool checkDirection(std::string dir, int x, int y, std::string word) {
    int dx = 0;
    int dy = 0;

    if (dir == "u") { 
        dy = -1;
    } else if (dir == "d") { 
        dy = 1;
    } else if (dir == "l") {
        dx = -1;
    } else if (dir == "r") {
        dx = 1;
    } else if (dir == "ul") { 
        dx = -1; dy = -1;
    } else if (dir == "ur") { 
        dx = 1; dy = -1;
    } else if (dir == "dr") { 
        dx = 1; dy = 1;
    } else if (dir == "dl") { 
        dx = -1; dy = -1;
    }

    for (int i = y; i < word.length(); i += dy) {
        for (int j = x; j < word.length(); i += dx) {
            if(puzzle[i][j] != filler || puzzle[i][j] != (char) word[j]) {
                return false;
            }
        }
    }
    return true;
}

static void fillVector(int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            puzzle[i][j] = filler;
        }
    }
}