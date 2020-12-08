#include <iostream>
#include <queue>

using namespace std;

vector<vector<int>> adj_matrix = {
    {INT_MAX, 21, 42, INT_MAX, INT_MAX, INT_MAX, 20, 7, 50, 14, 10, INT_MAX},
    {21, INT_MAX, 16, 32, INT_MAX, 16, INT_MAX, INT_MAX, 23, INT_MAX, 12, INT_MAX},
    {42, 16, INT_MAX, INT_MAX, 19, INT_MAX, 5, 32, 41, 20, INT_MAX, 17},
    {INT_MAX, 32, INT_MAX, INT_MAX, 33, 2, INT_MAX, INT_MAX, INT_MAX, 45, INT_MAX, INT_MAX},
    {INT_MAX, INT_MAX, 19, 33, INT_MAX, 27, INT_MAX, 16, 4, 19, INT_MAX, 80},
    {INT_MAX, 16, INT_MAX, 2, 27, INT_MAX, 10, 33, INT_MAX, 15, INT_MAX, INT_MAX},
    {20, INT_MAX, 5, INT_MAX, INT_MAX, 10, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 18},
    {7, INT_MAX, 32, INT_MAX, 16, 33, INT_MAX, INT_MAX, 11, 6, 45, INT_MAX},
    {50, 23, 41, INT_MAX, 4, INT_MAX, INT_MAX, 11, INT_MAX, 9, 28, 14},
    {14, INT_MAX, 20, 45, 19, 15, INT_MAX, 6, 9, INT_MAX, INT_MAX, 31},
    {10, 12, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 45, 28, INT_MAX, INT_MAX, 7},
    {INT_MAX, INT_MAX, 17, INT_MAX, 80, INT_MAX, 18, INT_MAX, 14, 31, 7, INT_MAX}
};



struct Vertex {
    int v, dist, prev;
    Vertex(int v, int dist, int prev) : v(v), dist(dist), prev(prev) { }
};

struct CompareV {
    bool operator() (Vertex *v1, Vertex *v2) {
        return v1->dist > v2->dist;
    }
};

//Dijkstra's algorithm
void dijkstra() {
    priority_queue<Vertex*, vector<Vertex*>, CompareV> queue;
    vector<int> dist(adj_matrix.size(), INT_MAX);
    vector<char> vis(adj_matrix.size(), 'F');
    vector<int> prev(adj_matrix.size(), -1);

    //Push the first vertex (Vertex 0) onto the queue
    queue.push(new Vertex(0, 0, INT_MAX));
    dist[0] = 0;
    
    int iteration = 0;

    while (!queue.empty()) {
        //Get the vertex with the shortest edge
        Vertex *V = queue.top(); queue.pop();

        //If the vertex has already been processed, skip and move to the next vertex in the queue.
        if (vis[V->v] == 'T')
            continue;
        
        //Prints the results of the previous iteration
        cout << "\n\n" << "Iteration " << iteration << '\n';
        cout << "V" << '\t' << "Vis" << '\t' << "Dist" << '\t' << "Prev" << '\n';
        for (int i = 0; i < (int) adj_matrix.size(); i++) {
            int temp = (dist[i] != INT_MAX) ? dist[i] : -1;
            cout << i << '\t' << vis[i] << '\t' << temp << '\t' << prev[i] << '\n'; 
        }
        cout << '\n';

        for (int i = 0; i < (int) adj_matrix.size(); i++) {
            if (adj_matrix[V->v][i] != INT_MAX) { //For each adjacent vertex of vertex V
                Vertex *adjV = new Vertex(i, adj_matrix[V->v][i], V->v);

                //If the distance of the current vertex is greater than the sum of the distance of vertex V
                //plus the distance of adjV, then the distance of adjV will be set to that sum
                if(dist[adjV->v] > dist[V->v] + adjV->dist) {
                    dist[adjV->v] = dist[V->v] + adjV->dist; //Update distance table
                    prev[adjV->v] = adjV->prev; //Update previous table (For the print portion)
                    adjV->dist = dist[adjV->v]; //Actually update the vertex's distance
                    queue.push(adjV); //Push that sucker to the queue
                }
            }
        }
        vis[V->v] = 'T'; //We need to keep track of what vertices we've already processed. Char instead of bool b/c it looks nicer when printed
        iteration++; //Purely for the printing portion to indicate which iteration its actually displaying
    }

    //Print out the final iteration of the program
    cout << "\n\n" << "Iteration " << iteration << '\n';
    cout << "V" << '\t' << "Vis" << '\t' << "Dist" << '\t' << "Prev" << '\n';
    for (int i = 0; i < (int) adj_matrix.size(); i++) {
        int temp = (dist[i] != INT_MAX) ? dist[i] : -1;
        cout << i << '\t' << vis[i] << '\t' << temp << '\t' << prev[i] << '\n'; 
    }
    cout << '\n';
}

int main() {
    dijkstra();
}