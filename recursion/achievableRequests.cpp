#include<iostream>
#include<vector>
#include<algorithm> 

using namespace std;

void solve(int idx,int count,vector<vector<int> >& request,vector<int>& resultant,int &result,int n,int m){
	if(idx >= m){
		bool isResultantZero = true;
		for(int x = 0; x<resultant.size();x++){
			if(resultant[x]!=0){
				isResultantZero = false;
				break;
			}
		}
		if(isResultantZero){
			result = max(result,count);
		}
		return;
	}	
	
	int from = request[idx][0]; //buildingindex
	int to = request[idx][1];
	
	resultant[from]--;
	resultant[to]++;
	
	solve(idx+1,count+1,request,resultant,result,n,m);
	
	resultant[from]++;
	resultant[to]--;
	
	solve(idx+1,count,request,resultant,result,n,m);

}

int maxReqAch(vector<vector<int> >& request, int n){
	int m = request.size();
	vector<int> resultant(n,0);	
	int result = INT_MIN;
	solve(0,0,request,resultant,result,n,m);
	return result;
}


int main(){
	vector<vector<int> > request = {{0,1},{1,0},{0,1}};
	int building = 2;
	int result = maxReqAch(request,building);
	cout<<result<<endl;
	return 0;
}
