#include <iostream>
#include <stack>
using namespace std;

bool rebundantBrackets(const string &s) {
    stack<char> st;
    
    for (int i = 0; i < s.length(); i++) {
        char ch = s[i];

        // If we encounter an opening bracket or an operator
        if (ch == '(' || ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            st.push(ch);
        } 
        // If we encounter a closing bracket
        else if (ch == ')') {
            bool isRedundant = true;
            while (!st.empty() && st.top() != '(') {
                char top = st.top();
                if (top == '+' || top == '-' || top == '*' || top == '/') {
                    isRedundant = false;
                }
                st.pop();
            } 
            if (isRedundant) {
                return true;
            }
            st.pop();
        }
    }

    return false; 
}

int main() {
    string s = "(a+(a+b))";
    cout << rebundantBrackets(s) << endl; // Outputs 0 (false)

    string s2 = "((a+b))";
    cout << rebundantBrackets(s2) << endl; // Outputs 1 (true)

    return 0;
}

