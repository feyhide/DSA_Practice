#include <iostream>
#include <stack>
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

bool toposortdfs(int** adj, int* sizes, bool* visited, bool* inStack, int u, stack<int>& s) {
    visited[u] = true;
    inStack[u] = true; 

    for (int i = 0; i < sizes[u]; i++) {
        int v = adj[u][i];
        if (!visited[v]) {
            if (!toposortdfs(adj, sizes, visited, inStack, v, s)) {
                return false; 
            }
        } else if (inStack[v]) {
            return false; 
        }
    }

    inStack[u] = false; 
    s.push(u);
    return true;
}

bool dfsForAllComponents(int vertices, int* sizes, int** adj) {
    bool* visited = new bool[vertices]{false};
    bool* inStack = new bool[vertices]{false}; 
    stack<int> s;
    bool isPossible = true;

    for (int i = 0; i < vertices; i++) {
        if (!visited[i] && sizes[i] != 0) {
            if (!toposortdfs(adj, sizes, visited, inStack, i, s)) {
                isPossible = false; 
                break;
            }
        }
    }

    if (isPossible) {
        cout << "Topological Sort: ";
        while (!s.empty()) {
            cout << s.top() << " ";
            s.pop();
        }
        cout << endl;
    } else {
        cout << "Topological Sort is not possible due to a cycle in the graph." << endl;
    }

    delete[] visited;
    delete[] inStack;
    return isPossible;
}

int main() {
    int vertices = 8; 
    Graph g(vertices);

    g.addEdge(5, 2, 1); 
    g.addEdge(5, 0, 1); 
    g.addEdge(4, 0, 1); 
    g.addEdge(4, 1, 1); 
    g.addEdge(2, 3, 1); 
    g.addEdge(3, 1, 1); 

    g.printAdjList();

    cout << "DFS Traversal for All Components and Topological Sort:\n";
    if (!dfsForAllComponents(vertices, g.sizes, g.adj)) {
        cout << "Topological Sort is not possible due to a cycle in the graph.\n";
    }

    return 0;
}

