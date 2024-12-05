#include <iostream>
using namespace std;

class Graph {
    int** adj;   // Adjacency list stored as a 2D array
    int vertices; // Number of vertices
    int* sizes;  // Array to track sizes of adjacency lists for each vertex

public:
    Graph(int v) {
        vertices = v;
        adj = new int*[v];       // Array of pointers for adjacency lists
        sizes = new int[v];      // Initialize sizes of lists

        for (int i = 0; i < v; i++) {
            adj[i] = new int[v]; // Allocate maximum space for each adjacency list
            sizes[i] = 0;        // Initially, all adjacency lists are empty
        }
    }

    void addEdge(int u, int v, bool direction) {
        adj[u][sizes[u]++] = v;  // Add edge from u to v
        if (direction == 0) {
            adj[v][sizes[v]++] = u; // Add edge from v to u if undirected
        }
    }

    void printAdjList() {
        for (int i = 0; i < vertices; i++) {
            cout << i << " -> ";
            for (int j = 0; j < sizes[i]; j++) {
                cout << adj[i][j] << ", ";
            }
            cout << endl;
        }
    }

    ~Graph() {
        for (int i = 0; i < vertices; i++) {
            delete[] adj[i];
        }
        delete[] adj;
        delete[] sizes;
    }
};

int main() {
    int vertices = 5; 
    Graph g(vertices);

    g.addEdge(0, 1, 0);
    g.addEdge(1, 2, 0);
    g.addEdge(2, 3, 0);
    g.addEdge(3, 1, 0);
    g.addEdge(3, 4, 0);
    g.addEdge(0, 4, 0);

    g.printAdjList();

    return 0;
}

