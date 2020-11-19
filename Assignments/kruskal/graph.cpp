//  Name: Miro Manestar
//  Assignment number: 5
//  Assignment: Breadth-first Search and Kruskal's Algorithm
//  File name: graph.cpp
//  Date last modified: November 12, 2020
//  Honor statement: I have neither given nor received any unauthorized help on this assignment.

//https://www.cs.southern.edu/halterman/Courses/Fall2020/318/Assignments/KruskalMST.html

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <queue>
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
    for (int i = 0; i < (int) size(); i++)
        for (int k = i; k < (int) size(); k++)
            if (adjacency_matrix[i][k] != NO_CONNECTION)
                sum += adjacency_matrix[i][k];
    return sum;
}

struct Vertex {
    int v, prev, dist;
    Vertex(int v) : v(v), prev(INT_MAX), dist(INT_MAX) { }
};

struct CompareV {
    bool operator() (Vertex *v1, Vertex *v2) {
        return v1->dist > v2->dist;
    }
};

int Graph::breadth_first_path_weight(const string& begin, const string& end) {
    //Create queue and push all vertexes to it
    priority_queue<Vertex*, vector<Vertex*>, CompareV> queue;
    for (int i = 0; i < size(); i++)
        queue.push(new Vertex(i));

    //Initialize first node
    queue.top()->dist = 0;

    while (!queue.empty()) {
        Vertex *v = queue.top(); queue.pop();
        if (v->dist == NO_CONNECTION) break;

        for (int i = 0; i < size(); i++) {
            if (adjacency_matrix[v->v][i] != NO_CONNECTION) {
                int dist = v->dist + adjacency_matrix[v->v][i];
                //if (dist < )
            }
        }
    }

    return INT_MAX;
}

class DisjointSet {
    std::vector<int> set;
public:
    DisjointSet(int numElements): set(numElements) { 
        this->Split();
    }

    //Returns the "parent" element of an equivalence class
    int Find(int i) {
        if (set[i] != i)
            set[i] = Find(set[i]);
        return set[i];
    }

    //Combines two equivalence classes, smaller class is pointed to the larger class
    void Union(int a, int b) {
        int set1 = Find(a);
        int set2 = Find(b);
        set[set1] = set2;
    }

    //Takes the set and puts each item into its own equivalence class
    void Split() {
        for (int i = 0; i < (int) set.size(); i++)
            set[i] = i;
    }
};

struct Edge {
    int weight, begin, end;
    Edge(int weight, int begin, int end) : weight(weight), begin(begin), end(end) { }
};
struct CompareWeight {
    bool operator() (Edge *e1, Edge *e2) {
        return e1->weight > e2->weight;
    }
};

/*
    Given a graph, select the smallest edge and check if it forms a cycle (That is, any vertice has more than one path to any other).
    Use a min-heap priority queue to sort all edges from smallest to largest
    To check if it is a cycle, use a disjoint set to determine if two vertices between an edge are already connected
    Repeat until the number of edges in the priority queue is # of vertices - 1
*/

Graph Graph::kruskal() {
    //Push edges to priority queue
    priority_queue<Edge*, vector<Edge*>, CompareWeight> queue;
    for (int i = 0; i < (int) size(); i++)
        for (int k = i; k < (int) size(); k++)
            if (adjacency_matrix[i][k] != INT_MAX)
                queue.push(new Edge(adjacency_matrix[k][i], i, k));

    //Create a copy of this graph object, then recreate adjacency matrix to be an MST
    Graph mst = *this;
    vector<vector<int>> temp(size(), vector<int>(size(), INT_MAX));
    mst.adjacency_matrix = temp;

    DisjointSet set(size()); //Determine if an edge will form a cycle
    while ((int) queue.size() > (int) size() - 1) { //If # of edges > vertices - 1
        Edge *e = queue.top(); queue.pop(); //Get smallest item
        int v1 = e->begin; int v2 = e->end;
        if (set.Find(v1) != set.Find(v2)) { //Determine if they will form a cycle
            set.Union(v1, v2); //If they do not, union them
            mst.adjacency_matrix[v1][v2] = e->weight;
            mst.adjacency_matrix[v2][v1] = e->weight;
        }
    }

    return mst;
}

ostream& operator<<(ostream& os, const Graph& g) {
    auto matrix = g.adjacency_matrix;

    //Determine the minimum column length
    int minFieldLength = 0;
    for (int i = 0; i < (int) matrix.size(); i++)
        if ((int) g.vertex_to_label_map[i].length() > minFieldLength)
            minFieldLength = g.vertex_to_label_map[i].length();
    minFieldLength += 4;

    //Print top header
    os << setw(minFieldLength + 4) << ' ';
    for (int i = 0; i < (int) matrix.size(); i++)
        os << setw(minFieldLength) << g.vertex_to_label_map[i];

    //Print separating line
    os << endl << right << setw(minFieldLength + 2) << "+" 
        << setfill('-') << setw(minFieldLength * g.size() + 4) << '-' << setfill(' ') << endl;

    //Print rows
    for (int i = 0; i < (int) matrix.size(); i++) {
        cout << right << setw(minFieldLength) << g.vertex_to_label_map[i] << " |";
        for (int val : matrix[i]) {
            if (val != g.NO_CONNECTION)
                cout << setw(minFieldLength) << val;
            else
                cout << setw(minFieldLength) << '-';
        }
        cout << endl;  
    }

    return os;
}