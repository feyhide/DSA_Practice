#include <iostream>
#include <vector>
using namespace std;

class WordSearch {
public:
    bool exist(vector<vector<char>>& board, string word) {
        int rows = board.size();
        int cols = board[0].size();
        vector<pair<int, int> > path;
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (backtrack(board, word, i, j, 0,path)) {
                    for(int k = 0; k < path.size(); k++){
                    	cout << "(" << path[k].first << "," << path[k].second << ") ";
                    }
                    cout << endl;
					return true;
                }
            }
        }
        return false;
    }

private:
    bool backtrack(vector<vector<char>>& board, const string& word, int row, int col, int index,vector<pair<int, int> >& path ) {
        if (index == word.size()) {
            return true;
        }

        if (row < 0 || row >= board.size() || col < 0 || col >= board[0].size() || board[row][col] != word[index]) {
            return false;
        }

		path.push_back({row, col});
        char temp = board[row][col];
        board[row][col] = '#'; 
	
        bool found = backtrack(board, word, row - 1, col, index + 1,path) ||  
                     backtrack(board, word, row + 1, col, index + 1,path) || 
                     backtrack(board, word, row, col - 1, index + 1,path) ||  
                     backtrack(board, word, row, col + 1, index + 1,path);    

        board[row][col] = temp;
		if (!found) {
            path.pop_back();
        }
        return found;
    }
};

int main() {
    vector<vector<char>> board = {
        {'B', 'B', 'C', 'E'},
        {'S', 'A', 'C', 'S'},
        {'Z', 'D', 'I', 'E'}
    };
    
    WordSearch ws;
    string word = "SADIE";
    
    if (ws.exist(board, word)) {
        cout << "Word found!" << endl;
    } else {
        cout << "Word not found." << endl;
    }
    
    return 0;
}

