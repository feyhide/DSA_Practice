#include<iostream>
#include<vector>
#include<unordered_set> 

using namespace std;

void solve(vector<vector<int> >& result,vector<int>& output,vector<int>& num,unordered_set<int>& st){
	if (num.size() == output.size()) {
        result.push_back(output);
        return;
    }	
    
    for(int i = 0; i < num.size();i++){
    	if(st.find(num[i]) == st.end()){
    		output.push_back(num[i]);
    		st.insert(num[i]);
    		solve(result,output,num,st);
			st.erase(num[i]);
			output.pop_back();
		}
	}
}

vector<vector<int> > getPermutation(vector<int>& nums){
	vector<vector<int> > result;
	vector<int> output;
	unordered_set<int> st;
	
	solve(result,output,nums,st);
	return result;
}


int main(){
	vector<int> nums = {1,2,3};
	vector<vector<int> > result = getPermutation(nums);
	for (int i = 0; i < result.size(); i++) {
        cout << "{ ";
        for (int j = 0; j < result[i].size(); j++) {
            cout << result[i][j] << " ";
        }
        cout << "}" << endl;
    }
	return 0;
}
