#include <iostream>
#include <vector>
#include <set>

using namespace std;

void solve(const vector<int>& s, vector<int>& output, int index, set<vector<int>>& ans) {
    // Base case: if we've considered all elements
    if (index >= s.size()) {
        if (!output.empty()) {
            ans.insert(output); // Store unique subsequences
        }
        return;
    }
    
    // Not include the current element
    solve(s, output, index + 1, ans);
    
    // Include the current element if it maintains an increasing order
    if (output.empty() || s[index] >= output.back()) {
        output.push_back(s[index]); // Add the current element
        solve(s, output, index + 1, ans);
        output.pop_back(); // Backtrack to explore other combinations
    }
}

vector<vector<int>> subsets(const vector<int>& s) {
    set<vector<int>> ans; // To store unique increasing subsequences
    vector<int> output;   // Current increasing subsequence
    int index = 0;
    solve(s, output, index, ans);
    return vector<vector<int>>(ans.begin(), ans.end()); // Convert set to vector for return
}

int main() {
    vector<int> s = {4, 6, 7, 7}; // Example input
    vector<vector<int>> ans = subsets(s);
    
    // Print the unique increasing subsequences
    for (const auto& subseq : ans) {
        cout << "[";
        for (size_t i = 0; i < subseq.size(); i++) {
            cout << subseq[i];
            if (i < subseq.size() - 1) {
                cout << ", ";
            }
        }
        cout << "]" << endl;
    }
    
    return 0;
}

