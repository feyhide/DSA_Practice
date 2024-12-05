#include<iostream>
#include<vector>

using namespace std;

bool isSafe(vector<vector<int>>& board, int n, int row, int col) {
    // Check the left side of the row
    for (int y = col; y >= 0; y--) {
        if (board[row][y] == 1) return false;
    }
    
    // Check the upper-left diagonal
    for (int x = row, y = col; x >= 0 && y >= 0; x--, y--) {
        if (board[x][y] == 1) return false;
    }
    
    // Check the lower-left diagonal
    for (int x = row, y = col; x < n && y >= 0; x++, y--) {
        if (board[x][y] == 1) return false;
    }
    
    return true;
}

void solve(vector<vector<int>>& board, int n, vector<vector<vector<int>>>& ans, int col) {
    if (col == n) {
        ans.push_back(board); // Directly push the board as a solution
        return;
    }

    for (int row = 0; row < n; row++) {
        if (isSafe(board, n, row, col)) {
            board[row][col] = 1; 
            solve(board, n, ans, col + 1);  
            board[row][col] = 0; 
        }
    }
}

vector<vector<vector<int>>> NQueen(int n) {
    vector<vector<int>> board(n, vector<int>(n, 0)); 
    vector<vector<vector<int>>> ans; 

    solve(board, n, ans, 0);
    return ans;
}

int main() {
    int n = 6; 
    vector<vector<vector<int>>> ans = NQueen(n);

    for (int k = 0; k < ans.size(); k++) {
        cout << "Solution " << k + 1 << ":" << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << (ans[k][i][j] == 1 ? "Q " : ". ");
            }
            cout << endl;
        }
        cout << endl;
    }

    return 0;
}

