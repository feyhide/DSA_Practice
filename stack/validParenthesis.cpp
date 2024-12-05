#include <iostream>
#include <stack>
using namespace std;

bool addprt(stack<char>& prtsis, char data) {
    if (data == '{' || data == '(' || data == '[') {
        prtsis.push(data);
    } else {
        if (!prtsis.empty()) {
            char top = prtsis.top();
            if ((top == '[' && data == ']') || 
                (top == '{' && data == '}') || 
                (top == '(' && data == ')')) {
                prtsis.pop(); 
            } else {
                return false; 
            }
        } else {
            return false;
        }
    }
    return true; 
}

int main() {
    stack<char> prtsis;

    string input = "{()([])}";
    bool isValid = true;

    for (int i = 0; i < input.length(); i++) {
        char ch = input[i];
        if (!addprt(prtsis, ch)) {
            isValid = false;
            break;
        }
    }

    if (isValid && prtsis.empty()) {
        cout << "The brackets are balanced." << endl;
    } else {
        cout << "The brackets are not balanced." << endl;
    }

    return 0;
}

