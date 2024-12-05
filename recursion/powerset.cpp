#include<iostream>
#include<vector>

using namespace std;

void solve(vector<int> nums, vector<int> output, int index, vector<vector<int> > &ans) {
    if(index >= nums.size()) {
        ans.push_back(output);
        return;
    }
    solve(nums, output, index + 1, ans);
    
    int el = nums[index];
    output.push_back(el);
    solve(nums, output, index + 1, ans);
}

vector<vector<int> > subsets(vector<int>& nums) {
    vector<vector<int> > ans;
    vector<int> output;
    int index = 0;
    solve(nums, output, index, ans);
    return ans;
}

int main() {
    int arr[] = {1, 2, 3};
    vector<int> nums(arr, arr + sizeof(arr) / sizeof(arr[0]));  // Convert array to vector
    
    vector<vector<int> > ans = subsets(nums);
    
    for(int i = 0; i < ans.size(); i++) {
        cout<<"[";
		for(int j = 0; j < ans[i].size(); j++) {
            cout << ans[i][j] << ",";
        }
        cout<<"]";
        cout << endl;
    }
    
    return 0;
}

