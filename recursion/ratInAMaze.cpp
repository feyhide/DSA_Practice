#include<iostream>
#include<vector>

using namespace std;

bool isSafe(vector<vector<int> >& maze,int n, int x, int y,vector<vector<int> > visited){
	if((x>=0 && x<n) && (y>=0 && y<n) && maze[x][y] == 1 && visited[x][y] == 0){
		return true;
	}
	return false;
}

void solveMaze(vector<vector<int> >& maze,int n,vector<string>& ans, int x, int y, string paths,vector<vector<int> > visited){
	if(x == n-1 && y == n-1){
		ans.push_back(paths);
		return;
	}	
	
	visited[x][y] = 1;
	int newx = x+1;
	int newy = y;
	if(isSafe(maze,n,newx,newy,visited)){
		paths.push_back('D');
		solveMaze(maze,n,ans,newx,newy,paths,visited);
		paths.pop_back();
	}
	
	newx = x;
	newy = y-1;
	if(isSafe(maze,n,newx,newy,visited)){
		paths.push_back('L');
		solveMaze(maze,n,ans,newx,newy,paths,visited);
		paths.pop_back();
	}
	
	newx = x;
	newy = y+1;
	if(isSafe(maze,n,newx,newy,visited)){
		paths.push_back('R');
		solveMaze(maze,n,ans,newx,newy,paths,visited);
		paths.pop_back();
	}
	
	newx = x-1;
	newy = y;
	if(isSafe(maze,n,newx,newy,visited)){
		paths.push_back('U');
		solveMaze(maze,n,ans,newx,newy,paths,visited);
		paths.pop_back();
	}
	visited[x][y] = 0;
}

vector<string> findPaths(vector<vector<int> >& maze,int n){
	vector<string> ans;
	string paths;
	vector<vector<int> > visited(n, vector<int>(n, 0));  // Initialize visited matrix to n x n with all zeros

	
	int srcx = 0;
	int srcy = 0;
	if (maze[0][0] == 1) {
        solveMaze(maze, n, ans, srcx, srcy, paths, visited);
    } else {
        cout << "No path available from start point." << endl;
    }
	return ans;
}

int main(){
	vector<vector<int> > maze = {
		{1,0,0,1},
		{1,0,1,1},
		{1,1,1,1},
		{0,0,0,1}
	};
	int n = 4;
	vector<string> ans = findPaths(maze,n);
	
	for(int i = 0; i < ans.size();i++){
		cout<<ans[i]<<endl;
	}

	return 0;
}
