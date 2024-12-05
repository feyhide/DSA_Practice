#include <iostream>
#include <vector>
#include <set>

using namespace std;

void solve(const vector<int>& s, vector<int>& output, int index, vector<vector<int>>& ans) {
    if (!output.empty()) {
        ans.push_back(output);
    }

    for (int i = index; i < s.size(); i++) {
        if (!output.empty() && abs(output.back() - s[i]) == 2) {
            continue; 
        }

        output.push_back(s[i]);
        solve(s, output, i + 1, ans);
        output.pop_back();
    }
}

vector<vector<int>> subsets(const vector<int>& s) {
    vector<vector<int>> ans;
    vector<int> output;  
    int index = 0;
    solve(s, output, index, ans);
    return ans;
}

int main() {
    vector<int> s = {2, 4, 6}; 
    vector<vector<int>> ans = subsets(s);
    
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

