#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "readfile.h"

std::vector<std::string> read_file(const std::string& filename) {
    std::vector<std::string> words;

    std::ifstream file(filename);
    std::string str;
    while (std::getline(file, str, ' ')) {
        words.push_back(str);
    }

    return words;
}

int main(int argc, char *argv[]) {
    if (argv[1] == nullptr) {
        std::cout << "No file given";
        return 0;
    }

    std::string filename(argv[1]);
    auto words  = read_file(filename);

    for (auto word : words) {
        std::cout << word << '\n';
    }
}
