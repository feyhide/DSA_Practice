#include<iostream>
#include<vector>

using namespace std;

// starts from 1 travel through all zeros and reach to 2 without touching -1

bool isSafe(vector<vector<int> >& maze, int n, int x, int y, int nonObs, int steps) {
    if ((x >= 0 && x < n) && (y >= 0 && y < n) && 
        ((maze[x][y] == 0 && steps < nonObs-1) || 
         (maze[x][y] == 2 && steps == nonObs-1))) {
        return true;
    }
    return false;
}

void solveMaze(vector<vector<int>>& maze, int n, vector<string>& ans, int x, int y, string path, int nonObs, int steps) {
    if (maze[x][y] == 2 && steps == nonObs) {
        ans.push_back(path);
        return;
    }
	int temp = maze[x][y];
    maze[x][y] = -1;

    int newX = x + 1;
    int newY = y;
    if (isSafe(maze, n, newX, newY, nonObs, steps)) {
        solveMaze(maze, n, ans, newX, newY, path + 'D', nonObs, steps + 1);
    }

    newX = x;
    newY = y - 1;
    if (isSafe(maze, n, newX, newY, nonObs, steps)) {
        solveMaze(maze, n, ans, newX, newY, path + 'L', nonObs, steps + 1);
    }

    newX = x;
    newY = y + 1;
    if (isSafe(maze, n, newX, newY, nonObs, steps)) {
        solveMaze(maze, n, ans, newX, newY, path + 'R', nonObs, steps + 1);
    }

    newX = x - 1;
    newY = y;
    if (isSafe(maze, n, newX, newY, nonObs, steps)) {
        solveMaze(maze, n, ans, newX, newY, path + 'U', nonObs, steps + 1);
    }

    maze[x][y] = temp;
}

vector<string> findPaths(vector<vector<int>>& maze, int n) {
    vector<string> ans;
    string path;
    int srcX = -1, srcY = -1;
    int nonObs = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (maze[i][j] == 1) {
                srcX = i;
                srcY = j;
                nonObs++;
            } else if (maze[i][j] == 0) {
                nonObs++;
            }
        }
    }

    if (srcX != -1 && srcY != -1) {
        solveMaze(maze, n, ans, srcX, srcY, path, nonObs, 0);
    } else {
        cout << "No valid starting point." << endl;
    }

    return ans;
}

int main() {
    vector<vector<int>> maze = {
        {0, 0, 1},
        {0, 0, 2},
        {0, 0, -1}
    };
    
    int n = 3;
    vector<string> ans = findPaths(maze, n);

    if (ans.empty()) {
        cout << "No valid path found." << endl;
    } else {
        for (int i = 0; i < ans.size(); i++) {
            cout << ans[i] << endl;
        }
    }

    return 0;
}

