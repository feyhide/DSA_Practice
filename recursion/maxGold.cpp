#include<iostream>
#include<vector>
#include <algorithm> // Include for max function

using namespace std;

int DFS(vector<vector<int> >& grid,int n,int i, int j){
	if(i >= n || i < 0 || j >= n || j < 0 || grid[i][j] == 0){
		return 0;
	}	
	
	int temp = grid[i][j];
	grid[i][j] = 0;
	
	int maxGold = 0;
	
	maxGold = max(maxGold, DFS(grid, n, i + 1, j)); // Down
    maxGold = max(maxGold, DFS(grid, n, i, j - 1)); // Left
    maxGold = max(maxGold, DFS(grid, n, i, j + 1)); // Right
    maxGold = max(maxGold, DFS(grid, n, i - 1, j)); // Up
	
	grid[i][j] = temp;
	
	return temp + maxGold;

}

int findmaxGold(vector<vector<int> >& grid,int n){
	int maxGold = 0;
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(grid[i][j] != 0){
				maxGold = max(maxGold,DFS(grid,n,i,j));
			}
		}
	}
	return maxGold;
}

int main(){
	vector<vector<int> > grid = {
		{0,6,0},
		{5,8,7},
		{0,9,0},
	};
	int n = 3;
	int ans = findmaxGold(grid,n);
	cout<<ans<<endl;

	return 0;
}
