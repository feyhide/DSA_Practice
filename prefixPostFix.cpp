#include <iostream>
#include <stack>
#include <string>

using namespace std;

// Function to determine the precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3; // ^ is for exponentiation
    return 0;
}

// Function to check if the character is an operator
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

// Function to check if the character is alphanumeric
bool isAlphanumeric(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9');
}

// Function to convert infix expression to postfix
string infixToPostfix(const string& infix) {
    stack<char> s;
    string postfix;

    for (int i = 0; i < infix.length(); i++) {
        char c = infix[i];

        // If the character is an operand, add it to output
        if (isAlphanumeric(c)) {
            postfix += c;
        } 
        // If the character is '(', push it to stack
        else if (c == '(') {
            s.push(c);
        } 
        // If the character is ')', pop and output from the stack until '(' is encountered
        else if (c == ')') {
            while (!s.empty() && s.top() != '(') {
                postfix += s.top();
                s.pop();
            }
            s.pop(); // Pop '('
        } 
        // An operator is encountered
        else if (isOperator(c)) {
            while (!s.empty() && precedence(s.top()) >= precedence(c)) {
                postfix += s.top();
                s.pop();
            }
            s.push(c);
        }
    }

    // Pop all the operators from the stack
    while (!s.empty()) {
        postfix += s.top();
        s.pop();
    }

    return postfix;
}

// Function to reverse a string
string reverseString(const string& str) {
    string reversed;
    for (int i = str.length() - 1; i >= 0; i--) {
        reversed += str[i];
    }
    return reversed;
}

// Function to convert infix expression to prefix
string infixToPrefix(const string& infix) {
    string reversedInfix = reverseString(infix);

    // Replace ( with ) and vice versa
    for (int i = 0; i < reversedInfix.length(); i++) {
        if (reversedInfix[i] == '(') {
            reversedInfix[i] = ')';
        } else if (reversedInfix[i] == ')') {
            reversedInfix[i] = '(';
        }
    }

    // Get postfix of the reversed expression
    string postfix = infixToPostfix(reversedInfix);

    // Reverse the postfix to get prefix
    return reverseString(postfix);
}

// Function to convert postfix expression to infix
string postfixToInfix(const string& postfix) {
    stack<string> s;

    for (int i = 0; i < postfix.length(); i++) {
        char c = postfix[i];

        // If the character is an operand, push it to the stack
        if (isAlphanumeric(c)) {
            s.push(string(1, c));
        } 
        // If the character is an operator
        else if (isOperator(c)) {
            string operand2 = s.top(); s.pop(); // Get the top two operands
            string operand1 = s.top(); s.pop();

            // Create a new expression in the form of (operand1 operator operand2)
            string newExpr = "(" + operand1 + c + operand2 + ")";
            s.push(newExpr); // Push the new expression back onto the stack
        }
    }

    // The last element of the stack is the final infix expression
    return s.top();
}

// Function to convert prefix expression to infix
string prefixToInfix(const string& prefix) {
    stack<string> s;

    // Iterate over the prefix expression in reverse order
    for (int i = prefix.length() - 1; i >= 0; i--) {
        char c = prefix[i];

        // If the character is an operand, push it to the stack
        if (isAlphanumeric(c)) {
            s.push(string(1, c));
        } 
        // If the character is an operator
        else if (isOperator(c)) {
            string operand1 = s.top(); s.pop(); // Get the top two operands
            string operand2 = s.top(); s.pop();

            // Create a new expression in the form of (operand1 operator operand2)
            string newExpr = "(" + operand1 + c + operand2 + ")";
            s.push(newExpr); // Push the new expression back onto the stack
        }
    }

    // The last element of the stack is the final infix expression
    return s.top();
}

int main() {
    string infix;

    cout << "Enter an infix expression: ";
    cin >> infix;

    string postfix = infixToPostfix(infix);
    string prefix = infixToPrefix(infix);

    cout << "Postfix expression: " << postfix << endl;
    cout << "Prefix expression: " << prefix << endl;

    // Additional conversion examples
    string postfixExpr, prefixExpr;

    cout << "Enter a postfix expression: ";
    cin >> postfixExpr;
    string infixFromPostfix = postfixToInfix(postfixExpr);
    cout << "Infix expression from postfix: " << infixFromPostfix << endl;

    cout << "Enter a prefix expression: ";
    cin >> prefixExpr;
    string infixFromPrefix = prefixToInfix(prefixExpr);
    cout << "Infix expression from prefix: " << infixFromPrefix << endl;

    return 0;
}

