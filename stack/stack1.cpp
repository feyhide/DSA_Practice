#include <iostream>
#include <stack>
using namespace std;

int main(){
	stack<int> s;
	s.push(3);
	s.push(2);
	s.push(1);
	cout<<"top:"<<s.top()<<endl;
	cout<<"is empty:"<<s.empty()<<endl;
	s.pop();
	cout<<"top:"<<s.top()<<endl;
	s.push(3);
	cout<<"top:"<<s.top()<<endl;
	cout<<"size:"<<s.size()<<endl;
	
	return 0;
}
