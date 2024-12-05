#include <iostream>
#include <stack>
#include <climits> // For INT_MIN

using namespace std;

const int MAX = 4;

// Function to find the next smaller element's index
void nextSmall(int arr[], int n, int next[]) {
    stack<int> s;
    s.push(-1);
    
    for (int i = n - 1; i >= 0; i--) {
        while (!s.empty() && arr[s.top()] >= arr[i]) {
            s.pop();
        }
        next[i] = s.empty() ? -1 : s.top();
        s.push(i);
    }
}

// Function to find the previous smaller element's index
void prevSmall(int arr[], int n, int prev[]) {
    stack<int> s;
    s.push(-1);
    
    for (int i = 0; i < n; i++) {
        while (!s.empty() && arr[s.top()] >= arr[i]) {
            s.pop();
        }
        prev[i] = s.empty() ? -1 : s.top();
        s.push(i);
    }
}

// Function to calculate the largest area rectangle in histogram
int largestAreaRec(int heights[], int n) {
    int next[n], prev[n];
    nextSmall(heights, n, next);
    prevSmall(heights, n, prev);
    int area = INT_MIN;

    for (int i = 0; i < n; i++) {
        int l = heights[i];
        if (next[i] == -1) {
            next[i] = n;
        }
        int b = next[i] - prev[i] - 1;

        int newArea = l * b;
        area = max(area, newArea);
    }
    return area;
}

// Function to find the maximum area of a rectangle formed by 1s in a binary matrix
int maxArea(int M[MAX][MAX], int n, int m) {
    int area = largestAreaRec(M[0], m); // Calculate for the first row
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < m; j++) {
            // Update the current row based on the previous row
            if (M[i][j] != 0) {
                M[i][j] = M[i][j] + M[i-1][j];
            } else {
                M[i][j] = 0;
            }
        }
        area = max(area, largestAreaRec(M[i], m)); // Process each row
    }
    return area;
}

int main() {
    int arr[MAX][MAX] = {
        {0, 1, 1, 0},
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {1, 1, 0, 0},
    };

    cout << maxArea(arr, MAX, MAX) << endl;

    return 0;
}

