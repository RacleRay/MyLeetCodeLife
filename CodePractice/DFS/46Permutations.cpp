// https://leetcode.com/problems/permutations/

#include <iostream>
#include <vector>

using namespace std;


class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        if (nums.size() == 0) return vector<vector<int>>{};
        vector<vector<int>> res;

        backtracking(nums, 0, res);
        return res;
    }

    void backtracking(vector<int> &nums, int level, vector<vector<int>>& ans) {
        if (level == nums.size() - 1) {
            ans.push_back(nums);
            return;
        }

        // i 从level开始，想想当前位置不变，继续下一个搜索的情况
        for (int i = level; i < nums.size(); ++i) {
            swap(nums[level], nums[i]);
            backtracking(nums, level + 1, ans);
            swap(nums[level], nums[i]);
        }

        return;
    }
};