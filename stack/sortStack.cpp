#include <iostream>
#include <stack>
using namespace std;

void sortedPush(stack<int>& s,int data) {
    if(s.empty() || (!s.empty() && s.top()<data)){
   		s.push(data);
		return;
	}
	int temp = s.top();
	s.pop();
	sortedPush(s,data);
	s.push(temp);
}

void sortStack(stack<int>& s) {
    if (s.empty()) {
        return;
    }
    
    int temp = s.top();
    s.pop();
    
    sortStack(s);
    
	sortedPush(s,temp);
}


int main() {
    stack<int> s;
    s.push(1);
    s.push(4);
    s.push(2);
    s.push(0);
    
    while (!s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;

    s.push(1);
    s.push(4);
    s.push(2);
    s.push(0); 
    sortStack(s);
    
	while (!s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;

    return 0;
}

