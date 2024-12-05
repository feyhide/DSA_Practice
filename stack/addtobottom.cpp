#include <iostream>
#include <stack>
using namespace std;

void ptb(stack<int>& s,int data) {
    if (s.empty()) {
        s.push(data);
        return; 
    }
    
    int temp = s.top();
    s.pop();
    
    ptb(s, data);
    
    s.push(temp);
}

int main() {
    stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
//    s.push(4);
//    s.push(5);
    ptb(s, 4);
    ptb(s, 5); 

    while (!s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;

    return 0;
}

