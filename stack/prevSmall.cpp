#include <iostream>
#include <stack>
#include <vector>

using namespace std;

vector<int> prevSmall(vector<int> &arr, int n) {
    stack<int> s;
    vector<int> ans(n);
    s.push(-1);
    
    for (int i = 0; i < n; i++) {
        while (!s.empty() && s.top() >= arr[i]) {
            s.pop();
        } 
        ans[i] = s.empty() ? -1 : s.top();
        s.push(arr[i]);
    }
    
    return ans;
}

int main() {
    vector<int> arr;
    arr.push_back(1);
    arr.push_back(5);
    arr.push_back(10);
    arr.push_back(9);
    
    vector<int> ans = prevSmall(arr, arr.size());
    
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " ";
    }
    cout << endl;

    return 0;
}

