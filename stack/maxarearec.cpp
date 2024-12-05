 #include <iostream>
#include <stack>
#include <vector>

using namespace std;

vector<int> nextSmall(vector<int> &arr, int n) {
    stack<int> s;
    vector<int> ans(n);
    s.push(-1);
    
    for (int i = n - 1; i >= 0; i--) {
        while (!s.empty() && arr[s.top()] >= arr[i]) {
            s.pop();
        }
        ans[i] = s.empty() ? -1 : s.top();
        s.push(i);
    }
    
    return ans;
}

vector<int> prevSmall(vector<int> &arr, int n) {
    stack<int> s;
    vector<int> ans(n);
    s.push(-1);
    
    for (int i = 0; i < n; i++) {
        while (!s.empty() && arr[s.top()] >= arr[i]) {
            s.pop();
        }
        ans[i] = s.empty() ? -1 : s.top();
        s.push(i);
    }
    
    return ans;
}

int largestAreaRec(vector<int>&heights){
	int n = heights.size();
	vector<int> next(n);
	next = nextSmall(heights,n);
	vector<int> prev(n);
	prev = prevSmall(heights,n);
	int area = INT_MIN;
	for(int i = 0 ; i < n; i++){
		int l = heights[i];
		if(next[i] == -1){
			next[i] = n;
		}
		int b = next[i] - prev[i] - 1;
		
		int newArea = l*b;
		area = max(area,newArea);
	}
	return area;
}

int main() {
    vector<int> arr;
    arr.push_back(2);
    arr.push_back(1);
    arr.push_back(5);
    arr.push_back(6);
    arr.push_back(2);
    arr.push_back(5);
    
    cout<<largestAreaRec(arr)<<endl;

    return 0;
}

