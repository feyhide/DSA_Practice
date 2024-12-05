#include<iostream>
#include<stack>

using namespace std;

void ptb(stack<int>& s,int data){
	if(s.empty()){
		s.push(data);
		return;
	}
	
	int temp = s.top();
	s.pop();
	
	ptb(s,data);
	
	s.push(temp);
}

void revstack(stack<int>& s){
	if(s.empty()){
		return;
	}
	
	int temp = s.top();
	s.pop();
	
	revstack(s);
	
	ptb(s,temp);
}

void printstack(stack<int> s){
	stack<int> temp = s;
	while(!temp.empty()){
		cout<<temp.top();
		temp.pop();
	}
	cout<<endl;
}

int main(){
	stack<int> s;
	s.push(1);
	s.push(2);
	s.push(3);
	
	printstack(s);
	
	revstack(s);
	
	printstack(s);
	
	return 0;
}
