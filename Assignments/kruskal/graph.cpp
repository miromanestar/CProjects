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
#include <sstream>
#include <regex>
#include "graph.h"

using namespace std;

Graph::Graph(const string& filename) {
    //Import and read the file
    ifstream inputFile;
    inputFile.open(filename);
    
    if (inputFile.is_open()) {
        string line;
        while (getline(inputFile, line)) {
            string buffer;
            stringstream ss(line);
            vector<string> filtered;
            while (ss >> buffer)
                filtered.push_back(buffer);
            
            if (vertex_to_label_map.empty()) { //If these are empty, it means we're still on the first line or the format is invalid
                for (int i = 0; i < (int) filtered.size(); i++) {
                    vertex_to_label_map.push_back(filtered[i]);
                    label_to_vertex_map[filtered[i]] = i;
                }
            } else { //Now let's fill in the adjacency matrix
                adjacency_matrix.push_back(vector<int>());
                for (int i = 1; i < (int) filtered.size(); i++) {
                    if (filtered[i] != "-")
                        adjacency_matrix.back().push_back(stoi(filtered[i])); //Convert string to integer if not "-"
                    else
                        adjacency_matrix.back().push_back(INT_MAX); //Using NO_CONNECTION yields an undefined reference error, but only here?
                }
            }

        }
        inputFile.close();
    }
}

int Graph::size() const {
    return adjacency_matrix.size();
}

int Graph::weight() const {
    int sum = 0;
    for (int i = 0; i < (int) adjacency_matrix.size(); i++)
        for (int k = i; k < (int) adjacency_matrix.size(); k++)
            if (adjacency_matrix[i][k] != NO_CONNECTION)
                sum += adjacency_matrix[i][k];
    return sum;
}

/*
    Use an array of bools to mark a vertex as visited after processing
    Use a queue to queue up processing all adjacent non-visited vertices
    If the vertice denoted by *end* is found, end

    TODO: Figure out how to maintain the weight of the path between begin and end
*/
int Graph::breadth_first_path_weight(const string& begin, const string& end) {
    return adjacency_matrix[label_to_vertex_map[begin]][label_to_vertex_map[end]];
}

/*
    Given a graph, select the smallest edge and check if it forms a cycle (That is, any vertice has more than one path to any other).
    Use a min-heap priority queue to sort all edges from smallest to largest
    To check if it is a cycle, use a disjoint set to determine if two vertices between an edge are already connected
    Repeat until the number of edges in the priority queue is # of vertices - 1

    https://www.geeksforgeeks.org/kruskals-minimum-spanning-tree-algorithm-greedy-algo-2/
*/
Graph Graph::kruskal() {
    return Graph("test");
}

ostream& operator<<(ostream& os, const Graph& g) {
    return os;
}