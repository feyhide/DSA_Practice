#include<iostream>
#include<queue>
using namespace std;



int main(){
	queue<int> q;
	q.push(11);
	q.push(23);
	q.push(1);
	
	cout<<q.size()<<endl;
	q.pop();
	cout<<q.size()<<endl;
	
	
	return 0;
}
