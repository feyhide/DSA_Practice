#include <iostream>
#include <vector>
#include <unordered_set>
#include <climits>
#include <algorithm>

using namespace std;

int minScore = INT_MAX;

void solve(vector<vector<int>>& result, vector<int>& output, vector<int>& num, unordered_set<int>& st, int score) {
    if(score > minScore){
    	return;
	}
	if (output.size() == num.size()) {
        score += abs(output.back() - num[output[0]]);
        if (score < minScore) {
            minScore = score;
            result.clear();
            result.push_back(output);
        }
        return;
    }

    for (int i = 0; i < num.size(); i++) {
        if (st.find(num[i]) == st.end()) {
            output.push_back(num[i]);
            st.insert(num[i]);
            int s = output.size();
            solve(result, output, num, st, score + (s > 1 ? abs(output[s - 2] - output[s - 1]) : 0));
            st.erase(num[i]);
            output.pop_back();
        }
    }
}

vector<vector<int>> getPermutation(vector<int>& nums) {
    vector<vector<int>> result;
    vector<int> output;
    unordered_set<int> st;
    solve(result, output, nums, st, 0);
    return result;
}

int main() {
    vector<int> nums = {1, 0, 2};
    vector<vector<int>> result = getPermutation(nums);
    
    for (int i = 0; i < result.size(); i++) {
        cout << "{ ";
        for (int j = 0; j < result[i].size(); j++) {
            cout << result[i][j] << " ";
        }
        cout << "}" << endl;
    }
    
    return 0;
}

