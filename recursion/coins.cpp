#include<iostream>
#include<vector>

using namespace std;

int sumofoutput(vector<int>& output){
	int sum = 0;
	for(int i = 0; i<output.size();i++){
		sum+=output[i];
	}
	return sum;
}

void solve(int idx,vector<vector<int> >& result,vector<int>& output,vector<int>& change,int val){
	if(sumofoutput(output) == val){
    	result.push_back(output);
    	return;
	}
	
	if(sumofoutput(output) > val){
		return;
	}
	
	for(int i = idx; i < change.size();i++){
    	output.push_back(change[i]);
		solve(i,result,output,change,val);
		output.pop_back();
	}
}

vector<vector<int> > getCoins(vector<int>& change,int val){
	vector<vector<int> > result;
	vector<int> output;
	solve(0,result,output,change,val);
	return result;
}


int main(){
	vector<int> change = {1,2,3};
	int val = 5;
	vector<vector<int> > result = getCoins(change,val);
	
	for (int i = 0; i < result.size(); i++) {
        cout << "{ ";
        for (int j = 0; j < result[i].size(); j++) {
            cout << result[i][j] << " ";
        }
        cout << "}" << endl;
    }
	return 0;
}
