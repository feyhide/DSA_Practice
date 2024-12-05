#include <iostream>
#include <stack>
#include <vector>

using namespace std;

bool knows(vector< vector<int> > &arr, int a, int b) {
    return arr[a][b] == 1;
}

int celeb(vector< vector<int> > &arr, int n) {
    stack<int> s;
    for (int i = 0; i < n; i++) {
        s.push(i); 
    }
    
    while (s.size() != 1) {
        int a = s.top();
        s.pop();
        int b = s.top();
        s.pop();
        
        if (knows(arr, a, b)) {
            s.push(b); 
        } else {
            s.push(a); 
        }
    }
    
    int candidate = s.top();
    
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[candidate][i] == 0) {
            count++;
        }
    }
    
    if (count != n) {
        return -1; 
    }
    
    count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i][candidate] == 1) {
            count++;
        }
    }
    
    if (count == n - 1) {
        return candidate; 
    } else {
        return -1; 
    }
}

int main() {
    vector< vector<int> > arr;
    vector<int> row1;
    row1.push_back(0);
    row1.push_back(0);
    row1.push_back(0);
    
    vector<int> row2;
    row2.push_back(1);
    row2.push_back(0);
    row2.push_back(0);
    
    vector<int> row3;
    row3.push_back(1);
    row3.push_back(1);
    row3.push_back(0);

    arr.push_back(row1);
    arr.push_back(row2);
    arr.push_back(row3);
    
    int n = arr.size();
    int celebrityIndex = celeb(arr, n);
    
    if (celebrityIndex != -1) {
        cout << "Celebrity is person: " << celebrityIndex << endl;
    } else {
        cout << "No celebrity found." << endl;
    }

    return 0;
}

