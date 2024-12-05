#include <iostream>
using namespace std;

class Graph {
public:
    int** adj;
    int vertices;
    int* sizes;

    Graph(int v) {
        vertices = v;
        adj = new int*[v];
        sizes = new int[v];

        for (int i = 0; i < v; i++) {
            adj[i] = new int[v];
            sizes[i] = 0;
        }
    }

    void addEdge(int u, int v, bool direction) {
        adj[u][sizes[u]++] = v;
        if (direction == 0) {
            adj[v][sizes[v]++] = u;
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

void bfs(int vertices, int* sizes, int** adj, int start, bool* visited) {
    int* traversal = new int[vertices];
    int front = 0, rear = 0;

    visited[start] = true;
    traversal[rear++] = start;

    while (front < rear) {
        int u = traversal[front++];
        cout << u << " ";

        for (int i = 0; i < sizes[u]; i++) {
            int v = adj[u][i];
            if (!visited[v]) {
                visited[v] = true;
                traversal[rear++] = v;
            }
        }
    }

    delete[] traversal;
}

void bfsForAllComponents(int vertices, int* sizes, int** adj) {
    bool* visited = new bool[vertices]{false};

    for (int i = 0; i < vertices; i++) {
        if (!visited[i] && sizes[i] != 0) {
            cout << "Component: ";
            bfs(vertices, sizes, adj, i, visited);
            cout << endl;
        }
    } 

    delete[] visited;
}

int main() {
    int vertices = 6; 
    Graph g(vertices);

    g.addEdge(0, 1, 0);
    g.addEdge(0, 3, 0);
    g.addEdge(4, 5, 0);

    g.printAdjList();

    cout << "BFS Traversal for All Components:\n";
    bfsForAllComponents(vertices, g.sizes, g.adj);

    return 0;
}

