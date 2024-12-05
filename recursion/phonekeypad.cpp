#include<iostream>
#include<vector>

using namespace std;

void solve(int idx,vector<string>& result,string output,string& digit,string mapping[]){
	if (idx == digit.length()) {
        result.push_back(output);
        return;
    }	
    
    if(digit[idx] == '0' || digit[idx] == '1'){
    	solve(idx+1,result,output,digit,mapping);
	}
	
	string temp = mapping[digit[idx]-'0'];
    for(int i = 0; i < temp.length();i++){
    	output.push_back(temp[i]);
    	solve(idx+1,result,output,digit,mapping);
		output.pop_back();
	}
}

vector<string> getPhoneKeyPad(string& digit){
	vector<string> result;
	string output;
	string mapping[10] = {"","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
	solve(0,result,output,digit,mapping);
	return result;
}


int main(){
	string digits = "23";
	vector<string> result = getPhoneKeyPad(digits);
	for (int i = 0; i < result.size(); i++) {
        cout<<result[i]<<endl;
    }
	return 0;
}
