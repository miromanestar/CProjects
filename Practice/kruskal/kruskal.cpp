#include <iostream>
#include <queue>

using namespace std;

vector<vector<int>> adj_matrix = {
    {INT_MAX, 21, 42, INT_MAX, INT_MAX, INT_MAX, 22, 71, 50, 24, 10, INT_MAX},
    {21, INT_MAX, 26, 32, INT_MAX, 16, INT_MAX, INT_MAX, 23, INT_MAX, 12, INT_MAX},
    {-42, 26, INT_MAX, INT_MAX, 29, INT_MAX, 5, 35, 41, 20, INT_MAX, 17},
    {INT_MAX, 32, INT_MAX, INT_MAX, 33, 2, INT_MAX, INT_MAX, INT_MAX, 45, INT_MAX, INT_MAX},
    {INT_MAX, INT_MAX, 29, 33, INT_MAX, 27, INT_MAX, 36, 4, 19, INT_MAX, 80},
    {INT_MAX, 16, INT_MAX, 2, 27, INT_MAX, 13, 38, INT_MAX, 15, INT_MAX, INT_MAX},
    {22, INT_MAX, 5, INT_MAX, INT_MAX, 13, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 18},
    {71, INT_MAX, 35, INT_MAX, 36, 38, INT_MAX, INT_MAX, 11, 6, 40, INT_MAX},
    {50, 23, 41, INT_MAX, 4, INT_MAX, INT_MAX, 11, INT_MAX, 9, 28, 14},
    {24, INT_MAX, 20, 45, 19, 15, INT_MAX, 6, 9, INT_MAX, INT_MAX, 31},
    {10, 12, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 40, 28, INT_MAX, INT_MAX, 7},
    {INT_MAX, INT_MAX, 17, INT_MAX, 80, INT_MAX, 18, INT_MAX, 14, 31, 7, INT_MAX}
};

int weight(vector<vector<int>> matrix) {
    int sum;
    for (int i = 0; i < (int) matrix.size(); i++)
        for (int k = i; k < (int) matrix.size(); k++)
            if (matrix[i][k] != INT_MAX)
                sum += matrix[i][k];
    return sum;
}

class DisjointSet {
    vector<int> set;
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

void kruskal() {
    int iteration = 0;
    //Push edges to priority queue
    priority_queue<Edge*, vector<Edge*>, CompareWeight> queue;
    for (int i = 0; i < (int) adj_matrix.size(); i++)
        for (int k = i; k < (int) adj_matrix.size(); k++)
            if (adj_matrix[i][k] != INT_MAX)
                queue.push(new Edge(adj_matrix[k][i], i, k));

    //Create a copy of this graph object, then recreate adjacency matrix to be an MST
    vector<vector<int>> mst(adj_matrix.size(), vector<int>(adj_matrix.size(), INT_MAX));

    DisjointSet set(mst.size()); //Determine if an edge will form a cycle
    while ((int) queue.size() > (int) mst.size() - 1) { //If # of edges > vertices - 1
        Edge *e = queue.top(); queue.pop(); //Get smallest item
        int v1 = e->begin; int v2 = e->end;
        if (set.Find(v1) != set.Find(v2)) { //Determine if they will form a cycle
            set.Union(v1, v2); //If they do not, union them
            mst[v1][v2] = e->weight;
            mst[v2][v1] = e->weight;

            iteration++;
            //Print out the MST
            cout << "Iteration: " << iteration << '\n';
            for (int i = 0; i < (int) mst.size(); i++)
                cout << '\t' << i;
            cout << '\n';
            for (int i = 0; i < (int) mst.size(); i++) {
                cout << i << '\t';
                for (int k = 0; k < (int) mst.size(); k++)
                    cout << ((mst[i][k] != INT_MAX) ? mst[i][k] : -1) << '\t';
                cout << '\n';
            }
            cout << "\n\n";
        }
    }
    cout << "Weight of MST: " << weight(mst) << '\n';
}

int main() {
    kruskal();
    cout << "Weight of Graph: " << weight(adj_matrix) << '\n';
}