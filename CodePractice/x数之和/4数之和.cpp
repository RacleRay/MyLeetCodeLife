/**
 * @file 4数之和.cpp

 给你一个由 n 个整数组成的数组 nums ，和一个目标值 target
。请你找出并返回满足下述全部条件且不重复的四元组 [nums[a], nums[b], nums[c],
nums[d]] （若两个四元组元素一一对应，则认为两个四元组重复）：

0 <= a, b, c, d < n
a、b、c 和 d 互不相同
nums[a] + nums[b] + nums[c] + nums[d] == target
你可以按 任意顺序 返回答案 。

 

示例 1：

输入：nums = [1,0,-1,0,-2,2], target = 0
输出：[[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
示例 2：

输入：nums = [2,2,2,2,2], target = 8
输出：[[2,2,2,2]]
 

提示：

1 <= nums.length <= 200
-109 <= nums[i] <= 109
-109 <= target <= 109

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/4sum
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

#include <bits/stdc++.h>
#include <iostream>
using namespace std;


class Solution {
public:
    // 方法一：递归简化问题为 k - 1
    // 的问题，可以使用DFS，DFS部分再说
    vector<vector<int>> fourSum1(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        return kSum(nums, target, 0, 4);
    }

    vector<vector<int>> kSum(vector<int>& nums, int target, int start, int k) {
        if (start == nums.size() || nums[start] - 1 > target / k
            || target / k > nums.back() + 1)
            return {};
        if (k == 2) return twoSum(nums, target, start);

        vector<vector<int>> res;
        for (int i = start; i < nums.size(); i++) {
            if (i > start && nums[i] == nums[i - 1])
                continue;  // skip duplicated
            // k-1 sum的结果+回溯
            vector<vector<int>> tmp =
                kSum(nums, target - nums[i], i + 1, k - 1);
            for (vector<int>& r : tmp) {
                r.push_back(nums[i]);
                res.push_back(std::move(r));
            }
        }
        return res;
    }

    vector<vector<int>> twoSum(vector<int>& nums, int target, int start) {
        vector<vector<int>> result;
        unordered_set<int>  uset;
        for (int i = start; i < nums.size(); i++) {
            if (!result.empty() && nums[i] == nums[i - 1]) continue;  // 去重
            // 查找
            int num2 = target - nums[i];
            if (uset.find(num2) != uset.end()) {
                result.push_back(std::move(vector<int>{num2, nums[i]}));
            }
            uset.insert(nums[i]);
        }
        return result;
    }


    // *********************************************************************
    // 方案二：排序 + 双指针，虽然同为 N^3 但是，这个会高效很多
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        if (nums.size() < 4 || nums[0] - 1 > target / 4
            || nums.back() + 1 < target / 4)
            return {};

        vector<vector<int>> result;
        for (int i = 0; i <= nums.size() - 4; i++) {
            // 去重
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            for (int j = i + 1; j <= nums.size() - 3; j++) {
                // 去重
                if (j > i + 1 && nums[j] == nums[j - 1]) continue;

                // 双指针遍历剩余部分
                int compliment = target - nums[i] - nums[j];
                _twoSum(nums, result, compliment, i, j);
            }
        }

        return result;
    }

    void _twoSum(vector<int>& nums, vector<vector<int>>& result,
                                int target, int i, int j) {
        int left = j + 1, right = nums.size() - 1;
        while (left < right) {
            // 去重
            if (left > j + 1 && nums[left] == nums[left - 1]) {
                left++;
                continue;
            };
            int twosum = nums[left] + nums[right];
            if (target < twosum) right--;
            if (target > twosum) left++;
            if (target == twosum)
                result.push_back({nums[i], nums[j], nums[left++], nums[right]});
        }
    }
};


int main(int argc, char* argv[]) {
    Solution    s = Solution();
    vector<int> nums{2, 2, 2, 2, 2};
    s.fourSum(nums, 8);
    return 0;
}