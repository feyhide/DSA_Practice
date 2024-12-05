#include<iostream>
#include<vector>

using namespace std;

void solve(string digit,int index,vector<string>& ans){
	if(index >= digit.length()){
		ans.push_back(digit);
		return;
	}	
	
	for(int j = index; j < digit.length(); j++){
		swap(digit[index],digit[j]);
		solve(digit,index+1,ans);
		swap(digit[index],digit[j]);
	}
}

vector<string> permutation(string digits){
	vector<string> ans;
	if(digits.length()==0){
		return ans;
	}
	int index = 0;
	solve(digits,index,ans);
	return ans;
}

int main(){
	string digits = "abc";
	vector<string> ans = permutation(digits);
	for(int i = 0; i < ans.size();i++){
		cout<<ans[i]<<endl;
	}
	return 0;
}
