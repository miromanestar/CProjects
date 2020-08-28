//DO NOT MODIFY

#include <iostream>
#include <string>
#include <vector>
#include <cctype>      //  For toupper
#include "wordsearch.h"

//  Reads words from the standard input stream and places them
//  into a vector.  (You can use redirection to load them from 
//  a file.)
//  Returns the resulting vector of words.
//  The first token in the text file is an integer representing 
//  the number of words in the file.
std::vector<std::string> get_words() {
    std::vector<std::string> result;   //  List of words to populate
    //  Do (or continue to do) loop while the stream has data
    std::string word;
    while (std::cin >> word) {    
        //  Ensure all letters are uppercase
        for (char& ch : word) 
            ch = static_cast<char>(toupper(ch));
        //  Add word to the list
       result.push_back(word);
    }
    return result;  //  Return the list of words from the file
}


int main() {
    std::vector<std::string> word_list = get_words();
    //  Build a 20 x 20 word search key
    LetterMatrix key = make_key(word_list, 20, 20);
    //  Build a corresponding puzzle from the key
    LetterMatrix puz = make_puzzle(key);
    //  Print the list of words
    for (auto word : word_list)
        std::cout << word << '\n';
    std::cout << '\n';
    //  Print the puzzle
    std::cout << puz << '\n';
    //  Print the key
    std::cout << key << '\n';
}
