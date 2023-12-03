#include <iostream>
#include <vector>

using namespace std;

// https://leetcode.com/problems/combinations/

class Solution {
public:
    // 排列回溯的是交换位置，组合回溯的是是否将当前元素加入结果
    vector<vector<int>> combine(int n, int k) {
        if (k > n || k == 0 || n == 0) return vector<vector<int>>{};
        vector<vector<int>> res;
        vector<int> nums;
        nums.reserve(k);
        backtracking(1, n, k, nums, res);
        return res;
    }

    void backtracking(int elem, int n, int k, vector<int>& nums, vector<vector<int>>& ans) {
        if (nums.size() == k) {
            ans.push_back(nums);
            return;
        }

        for (int i = elem; i <= n; ++i) {
            nums.push_back(i);
            backtracking(i + 1, n, k, nums, ans);
            nums.pop_back();
        }
    }
};