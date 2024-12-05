#include<iostream>

using namespace std;

string revString(string s,int start,int end){
	if(start>=end){
		return s;
	}
	swap(s[start],s[end]);
	return revString(s,start+1,end-1);
}

int main(){
	string s = "fahad";
	int size = s.size() - 1;
	string revS = revString(s,0,size);
	cout<<revS<<endl;
	return 0;
}
