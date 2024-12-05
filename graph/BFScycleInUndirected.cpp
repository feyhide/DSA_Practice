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

bool bfs(int vertices, int* sizes, int** adj, int start, bool* visited,int *parent) {
    int* traversal = new int[vertices];
    int front = 0, rear = 0;

    visited[start] = true;
    traversal[rear++] = start;
    parent[start] = -1;

    while (front < rear) {
        int u = traversal[front++];
        cout << u << " ";

        for (int i = 0; i < sizes[u]; i++) {
            int v = adj[u][i];
            if (!visited[v] && parent[u] != v) {
                visited[v] = true;
                traversal[rear++] = v;
                parent[v] = u;
            }else if(visited[v] && parent[u] != v){	
    			delete[] traversal;
				return true;
			}
        }
    }
    delete[] traversal;
	return false;
}

bool bfsForAllComponents(int vertices, int* sizes, int** adj) {
    bool* visited = new bool[vertices]{false};
	int* parent = new int[vertices];	
    int check;
	for (int i = 0; i < vertices; i++) {
        if (!visited[i] && sizes[i] != 0) {
            cout << "Component: ";
            if (bfs(vertices, sizes, adj, i, visited, parent)) {
                delete[] visited;
                delete[] parent; 
				cout << endl;
                return true;
            }
			cout << endl;
        }
    } 

    delete[] visited;
    delete[] parent;
    return false;
}

int main() {
    int vertices = 6; 
    Graph g(vertices);

    g.addEdge(0, 1, 0);
    g.addEdge(0, 3, 0);
    g.addEdge(4, 5, 0);

    g.printAdjList();

    if (bfsForAllComponents(vertices, g.sizes, g.adj)) {
        cout << "Cycle detected in the graph.\n";
    } else {
        cout << "No cycle detected in the graph.\n";
    }

    return 0;
}

