#include <iostream>
#include <vector>
#include <set>

using namespace std;

// Function to check if a substring is a palindrome
bool isPalindrome(const string& s, int left, int right) {
    while (left < right) {
        if (s[left] != s[right]) return false;
        left++;
        right--;
    }
    return true;
}

void solve(string s, int idx, vector<string>& curr, vector<vector<string>>& result) {
    if (idx == s.length()) {
        result.push_back(curr);
        return;
    }
    
    for (int i = idx; i < s.length(); i++) {
        if (isPalindrome(s, idx, i)) {
            curr.push_back(s.substr(idx, i - idx + 1));  // Corrected here
            solve(s, i + 1, curr, result);
            curr.pop_back();
        }
    }
}

vector<vector<string>> backtrack(string s) {
    vector<vector<string>> ans;
    vector<string> curr;
    solve(s, 0, curr, ans);
    return ans;
}

int main() {
    string s = "anasa";  // Missing semicolon added
    vector<vector<string>> ans = backtrack(s); 
    for (int i = 0; i < ans.size(); i++) {
        for (const string& str : ans[i]) {
            cout << str << " ";
        }
        cout << endl;  // Print partitions in one line
    }
    return 0;
}

