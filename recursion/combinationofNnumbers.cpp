#include<iostream>
#include<vector>
#include<algorithm> 

using namespace std;

void solve(int idx,int n,vector<vector<int> >& result,vector<int>& number,vector<int>& output,int comb){
	if (output.size() == comb) {
        result.push_back(output);
        return;
    }	
    
    if (idx >= n) {
        return;
    }
    
	output.push_back(number[idx]);
	solve(idx+1,n,result,number,output,comb);
	output.pop_back();
	solve(idx+1,n,result,number,output,comb);
}

vector<vector<int> > getcomb(int n,int comb){
	vector<vector<int> > result;
	vector<int> output;
	vector<int> numbers(n);
	for(int i = 0; i < n; i++){
		numbers[i] = i+1;
	}
	
	solve(0,n,result,numbers,output,comb);
	return result;
}


int main(){
	int n = 4;
	int comb = 2;
	vector<vector<int> > result = getcomb(n,comb);
	for (int i = 0; i < result.size(); i++) {
        cout << "{ ";
        for (int j = 0; j < result[i].size(); j++) {
            cout << result[i][j] << " ";
        }
        cout << "}" << endl;
    }
	return 0;
}
