#include <iostream>
using namespace std;

class Node {
public:
    Node* next;
    int data;

    Node(int data) {
        this->data = data;
        this->next = NULL;
    }
};

class Stack {
private:
    Node* start;
    int top;

public:
    Stack(int data) {
        this->start = new Node(data);
        this->top = 0;
    }

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    void push(int data) {
        Node* temp = new Node(data);
        temp->next = start;
        start = temp;
        top++;
    }

    void pop() {
        if (isEmpty()) {
            cout << "Stack underflow" << endl;
            return;
        }
        Node* temp = start;
        start = start->next;
        delete temp;
        top--;
    }

    int peek() {
        if (!isEmpty()) {
            return start->data;
        }
        cout<<"Stack is empty"<<endl;
    }

    bool isEmpty() {
        return top == 0;
    }

    int stacksize() {
        return top+1;
    }
};

int main() {
    Stack st(5);
    cout << "Stack size: " << st.stacksize() << endl;
    st.push(22);
    cout << "Stack size: " << st.stacksize() << endl;
    st.push(43);
    cout << "Stack size: " << st.stacksize() << endl;
    st.pus h(101);
    cout << "Stack size: " << st.stacksize() << endl;
    cout << "Top element: " << st.peek() << endl;
    st.pop();
    cout << "Top element: " << st.peek() << endl;
    st.pop();
    cout << "Top element: " << st.peek() << endl;
    cout << "Empty: " << (st.isEmpty() ? "Yes" : "No") << endl;
    cout << "Stack size: " << st.stacksize() << endl;
    st.pop();
    st.pop(); 
    cout << "Empty: " << (st.isEmpty() ? "Yes" : "No") << endl;
    cout << "Stack size: " << st.stacksize() << endl;
    st.peek();

	return 0;
}

