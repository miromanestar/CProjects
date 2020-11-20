//  Name: Miro Manestar
//  Assignment number: 5
//  Assignment: Breadth-first Search and Kruskal's Algorithm
//  File name: graph.cpp
//  Date last modified: November 19, 2020
//  Honor statement: I have neither given nor received any unauthorized help on this assignment.

/*
    For whatever reason, using NO_CONNECTION by itself in this file causes g++ to complain about
    Graph::NO_CONNECTION being an undefined reference. Weirdly enough, sometimes NO_CONNECTION will compile,
    but it seems to be kind of random....
    I really don't know what to do about it so for now I'm just using NO_CONNECTION
*/

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <queue>
#include "graph.h"

Graph::Graph(const std::string& filename) {
    //Import and read the file
    std::ifstream inputFile;
    inputFile.open(filename);
    
    if (inputFile.is_open()) {
        std::string line;
        while (getline(inputFile, line)) {
            std::string buffer;
            std::stringstream ss(line);
            std::vector<std::string> filtered;
            while (ss >> buffer)
                filtered.push_back(buffer);
            
            if (vertex_to_label_map.empty()) { //If these are empty, it means we're still on the first line or the format is invalid
                for (int i = 0; i < (int) filtered.size(); i++) {
                    vertex_to_label_map.push_back(filtered[i]);
                    label_to_vertex_map[filtered[i]] = i;
                }
            } else { //Now let's fill in the adjacency matrix
                adjacency_matrix.push_back(std::vector<int>());
                for (int i = 1; i < (int) filtered.size(); i++) {
                    if (filtered[i] != "-")
                        adjacency_matrix.back().push_back(stoi(filtered[i])); //Convert std::string to integer if not "-"
                    else
                        adjacency_matrix.back().push_back((int) NO_CONNECTION); //Using NO_CONNECTION yields an undefined reference error, but only here
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
    int v, dist;
    Vertex(int v, int dist) : v(v), dist(dist) { }
};

struct CompareV {
    bool operator() (Vertex *v1, Vertex *v2) {
        return v1->dist > v2->dist;
    }
};

int Graph::breadth_first_path_weight(const std::string& begin, const std::string& end) {
    //Create queue
    std::priority_queue<Vertex*, std::vector<Vertex*>, CompareV> queue;

    //Create std::vector for distances
    std::vector<int> dist(size(), INT_MAX);

    //Push first vertex to queue and set distance as 0
    queue.push(new Vertex(label_to_vertex_map[begin], 0));
    dist[label_to_vertex_map[begin]] = 0;

    while (!queue.empty()) {
        Vertex *v = queue.top(); queue.pop();

        //Go through all adjacent vertices of v
        for (int i = 0; i < size(); i++) {
            if (adjacency_matrix[v->v][i] != NO_CONNECTION) {
                //Get adjacent vertex data
                Vertex *adjV = new Vertex(i, adjacency_matrix[v->v][i]);

                if (dist[adjV->v] > dist[v->v] + adjV->dist) {
                    dist[adjV->v] = dist[v->v] + adjV->dist;
                    queue.push(adjV);
                }
            }
        }
    }

    return dist[label_to_vertex_map[end]];
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
    std::priority_queue<Edge*, std::vector<Edge*>, CompareWeight> queue;
    for (int i = 0; i < (int) size(); i++)
        for (int k = i; k < (int) size(); k++)
            if (adjacency_matrix[i][k] != NO_CONNECTION)
                queue.push(new Edge(adjacency_matrix[k][i], i, k));

    //Create a copy of this graph object, then recreate adjacency matrix to be an MST
    Graph mst = *this;
    std::vector<std::vector<int>> temp(size(), std::vector<int>(size(), (int) NO_CONNECTION));
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

std::ostream& operator<<(std::ostream& os, const Graph& g) {
    auto matrix = g.adjacency_matrix;

    //Determine the minimum column length
    int minFieldLength = 0;
    for (int i = 0; i < (int) matrix.size(); i++)
        if ((int) g.vertex_to_label_map[i].length() > minFieldLength)
            minFieldLength = g.vertex_to_label_map[i].length();
    minFieldLength += 4;

    //Print top header
    os << std::setw(minFieldLength + 4) << ' ';
    for (int i = 0; i < (int) matrix.size(); i++)
        os << std::setw(minFieldLength) << g.vertex_to_label_map[i];

    //Print separating line
    os << std::endl << std::right << std::setw(minFieldLength + 2) << "+" 
        << std::setfill('-') << std::setw(minFieldLength * g.size() + 4) << '-' << std::setfill(' ') << std::endl;

    //Print rows
    for (int i = 0; i < (int) matrix.size(); i++) {
        std::cout << std::right << std::setw(minFieldLength) << g.vertex_to_label_map[i] << " |";
        for (int val : matrix[i]) {
            if (val != g.NO_CONNECTION)
                std::cout << std::setw(minFieldLength) << val;
            else
                std::cout << std::setw(minFieldLength) << '-';
        }
        std::cout << std::endl;  
    }

    return os;
}