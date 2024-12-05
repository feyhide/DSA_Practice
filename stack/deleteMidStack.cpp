#include <iostream>
#include <stack>
using namespace std;

void solve(stack<int>& input, int count, int n) {
    if (count == n / 2) {
        input.pop(); 
        return;
    }

    int temp = input.top();
    input.pop(); 
    solve(input, count + 1, n); 
    input.push(temp); 
}

void deleteMid(stack<int>& input, int n) {
    int count = 0;
    solve(input, count, n);
}

int main() {
    stack<int> input;
    input.push(5);
    input.push(3);
    input.push(2);
    input.push(1);
    input.push(0);

    deleteMid(input, input.size());

    while (!input.empty()) {
        cout << input.top() << " ";
        input.pop();
    }

    return 0;
}

