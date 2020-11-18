//  Name: Miro Manestar
//  Assignment number: 5
//  Assignment: Breadth-first Search and Kruskal's Algorithm
//  File name: graph.cpp
//  Date last modified: November 12, 2020
//  Honor statement: I have neither given nor received any unauthorized help on this assignment.

//https://www.cs.southern.edu/halterman/Courses/Fall2020/318/Assignments/KruskalMST.html

#include <string>
#include <iostream>
#include <fstream>
#include "graph.h"

using namespace std;

Graph::Graph(const string& filename) {
    //Import and read the file
    ifstream inputFile;
    inputFile.open(filename);
    
    if (inputFile.is_open()) {
        string line;
        while (getline(inputFile, line)) {
            //Scout << line << '\n';
        }
        inputFile.close();
    }
}

int Graph::size() const {
    return 0;
}

int Graph::weight() const {
    return 0;
}

int Graph::breadth_first_path_weight(const string& begin, const string& end) {
    return 0;
}

Graph Graph::kruskal() {
    return Graph("test");
}

ostream& operator<<(ostream& os, const Graph& g) {
    return os;
}