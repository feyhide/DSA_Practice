#include <iostream>
using namespace std;

class NStack {
public:
    int* arr;
    int* top;
    int* next;
    int freespot;
    int n, s;

    NStack(int N, int S) {
        n = N;
        s = S;
        arr = new int[s];
        top = new int[n];
        next = new int[s];
        for (int i = 0; i < n; i++) {
            top[i] = -1;
        }
        for (int i = 0; i < s; i++) {
            next[i] = i + 1;
        }
        next[s - 1] = -1;
        freespot = 0;
    }

    bool push(int x, int m) {
        if (m < 1 || m > n) {
            cout << "Invalid stack number." << endl;
            return false;
        }
        if (freespot == -1) {
            cout << "Stack overflow." << endl;
            return false;
        }
        int index = freespot;
        freespot = next[index];
        arr[index] = x;
        next[index] = top[m - 1];
        top[m - 1] = index;
        return true;
    }

    int pop(int m) {
        if (m < 1 || m > n) {
            cout << "Invalid stack number." << endl;
            return -1;
        }
        if (top[m - 1] == -1) {
            cout << "Stack underflow." << endl;
            return -1;
        }
        int index = top[m - 1];
        top[m - 1] = next[index];
        next[index] = freespot;
        freespot = index;
        return arr[index];
    }

    int peek(int m) {
        if (m < 1 || m > n) {
            cout << "Invalid stack number." << endl;
            return -1;
        }
        if (top[m - 1] == -1) {
            cout << "Stack is empty." << endl;
            return -1;
        }
        return arr[top[m - 1]];
    }

    ~NStack() {
        delete[] arr;
        delete[] top;
        delete[] next;
    }
};

int main() {
    NStack ns(3, 6);
    ns.push(10, 1);
    ns.push(11, 2);
    ns.push(12, 1);
    ns.push(14, 3);
    ns.push(3, 1);
    ns.push(9, 1);
    ns.push(18, 3);
    ns.push(15, 3);
    
    cout << "Popped from stack 1: " << ns.pop(1) << endl;
    cout << "Popped from stack 2: " << ns.pop(2) << endl;
    cout << "Popped from stack 3: " << ns.pop(3) << endl;
    cout << "Popped from stack 1: " << ns.pop(1) << endl;
    cout << "Popped from stack 1: " << ns.pop(1) << endl;

    return 0;
}

