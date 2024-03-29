// KruskalsMST.cpp
// Created 11/5/2019 8:25:28 PM

#include <iostream>
#include "graph.h"

int main() {
    Graph g{"distance.table"};
    
    std::cout << g << '\n'; 
    std::cout << "Graph edge weights: " << g.weight() << '\n';
    std::cout << "\n====================================================\n\n"; //hey miro i assume you are working so ill stop bothering you :)
    Graph mst = g.kruskal();
    std::cout << mst << '\n'; 
    std::cout << "Graph edge weights: " << mst.weight() << '\n';

    
    int path_weight = mst.breadth_first_path_weight("London", "Moscow");
    if (path_weight == Graph::NO_CONNECTION) {
        std::cout << "No such path exists\n";
    }
    else {
        std::cout << "London to Moscow path length: " << path_weight << '\n';
    }
}