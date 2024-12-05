#include<iostream>
#include<vector>
#include<algorithm> 

using namespace std;

void solve(int idx,vector<int>& cookies,vector<int>& children,int k,int &result,int n){
	if(idx >= n){
		int unfairness = *max_element(begin(children),end(children));
		result = min(result,unfairness);
		return;
	}	
	
	int cookie = cookies[idx];
	for(int i = 0; i < k; i++){
		children[i] += cookie;
		solve(idx+1,cookies,children,k,result,n);
		children[i] -= cookie;
	}
}

int cookieFairDistribution(vector<int>& cookies, int k){
	int n = cookies.size();
	int result = INT_MAX;
	vector<int> children(k,0);	
	solve(0,cookies,children,k,result,n);
	return result;
}


int main(){
	vector<int> cookies = {10,5,10};
	int noOFchildren = 2;
	int result = cookieFairDistribution(cookies,noOFchildren);
	cout<<result<<endl;
	return 0;
}
