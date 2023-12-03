#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>


using namespace std;

class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> res;
        if (nums.size() < 1) return res;

        vector<bool> visited(nums.size(), 0);
        vector<int> path;

        sort(nums.begin(), nums.end(), std::less<int>());
        dfs(nums, res, visited, path);

        return res;
    }

    void dfs(vector<int>& nums, vector<vector<int>>& res, vector<bool>& visited, 
            vector<int> path) {
        if (path.size() == nums.size()) {
            res.push_back(path);
            return;
        }

        for (int i = 0; i < nums.size(); ++i) {
            if (visited[i]) continue;
            if ((i > 0) && (nums[i] == nums[i - 1]) && !visited[i - 1])
                continue;

            path.push_back(nums[i]);
            visited[i] = 1;
            dfs(nums, res, visited, path);
            visited[i] = 0;
            path.pop_back();
        }
    }
};