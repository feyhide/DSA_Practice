#include <iostream>
#include <queue>
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

void CheckCyclic(int vertices, int* sizes, int** adj) {
    int* indegree = new int[vertices] {0}; 
    queue<int> q;
    int* topologicalOrder = new int[vertices];
    int index = 0;

    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < sizes[i]; j++) {
            int v = adj[i][j];
            indegree[v]++;
        }
    }

    for (int i = 0; i < vertices; i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topologicalOrder[index++] = u;

        for (int i = 0; i < sizes[u]; i++) {
            int v = adj[u][i];
            indegree[v]--;
            if (indegree[v] == 0) {
                q.push(v);
            }
        }
    }

    if (index != vertices) {
        cout << "Cyclic\n";
    } else {
        cout << "Not a Cyclic ";
//        for (int i = 0; i < vertices; i++) {
//            cout << topologicalOrder[i] << " ";
//        }
        cout << endl;
    }

    delete[] indegree;
    delete[] topologicalOrder;
}

int main() {
    int vertices = 6; 
    Graph g(vertices);

    g.addEdge(5, 2, 0); 
    g.addEdge(5, 0, 0);
    g.addEdge(4, 0, 0);
    g.addEdge(4, 1, 0);
    g.addEdge(2, 3, 0);
    g.addEdge(3, 1, 0);

    g.printAdjList();

    CheckCyclic(vertices, g.sizes, g.adj);
	
    return 0;
}

