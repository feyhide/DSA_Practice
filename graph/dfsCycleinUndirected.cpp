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

bool dfs(int** adj, int* sizes, bool* visited, int u,int parent) {
    visited[u] = true;
	
    for (int i = 0; i < sizes[u]; i++) {
        int v = adj[u][i];
        if (!visited[v]) {
            if(dfs(adj, sizes, visited, v, u)){
            	return true;
			}
        }else if(v != parent){
        	return true;
		}
    }
    return false;
}

bool dfsForAllComponents(int vertices, int* sizes, int** adj) {
    bool* visited = new bool[vertices]{false};

    for (int i = 0; i < vertices; i++) {
        if (!visited[i] && sizes[i] != 0) {
            if(dfs(adj, sizes, visited, i,-1)){
            	delete[] visited;
            	return true;
			}
        }
    }

    delete[] visited;
    return false;
}

int main() {
    int vertices = 8; 
    Graph g(vertices);

    
    g.addEdge(0, 1, 0);
    g.addEdge(0, 3, 0);
    g.addEdge(4, 5, 0);

    g.printAdjList();

    cout << "DFS Traversal for All Components:\n";
    cout << dfsForAllComponents(vertices, g.sizes, g.adj);

    return 0;
}

