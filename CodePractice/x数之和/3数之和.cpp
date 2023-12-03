/*************************************************************************
    > File Name: 3数之和.cpp
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time:
 ************************************************************************/

#include <bits/stdc++.h>
#include <iostream>
using namespace std;


/**
给你一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，使得 a
+ b + c = 0 ？请你找出所有和为 0 且不重复的三元组。

注意：答案中不可以包含重复的三元组。

 

示例 1：

输入：nums = [-1,0,1,2,-1,-4]
输出：[[-1,-1,2],[-1,0,1]]
示例 2：

输入：nums = []
输出：[]
示例 3：

输入：nums = [0]
输出：[]
 

提示：

0 <= nums.length <= 3000
-105 <= nums[i] <= 105

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/3sum
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        if (nums.size() < 3) return {};

        int nsize = nums.size();

        vector<vector<int>> result;

        sort(nums.begin(), nums.end());
        if (nums[0] > 0 || nums[nsize - 1] < 0) return {}; // 剪枝

        for (int i = 0; i < nsize - 2; ++i) {
            // 跳过重复
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            int target = -nums[i];
            int left = i + 1, right = nsize - 1;

            // search for two sum
            twoSum(result, nums, target, left, right);
        }

        return result;
    }

    void twoSum(vector<vector<int>>& result, vector<int>& nums, int target,
                int start, int end) {
        while (start < end) {
            int two_sum = nums[start] + nums[end];
            if (two_sum < target)
                start++;
            else if (two_sum > target)
                end--;
            else {
                result.push_back(std::move(
                    vector<int>{-target, nums[start++], nums[end--]}));
                // 跳过重复
                while (start < end && nums[start] == nums[start - 1])
                    start++;
                while (start < end && nums[end] == nums[end + 1])
                    end--;
            }
        }

        return;
    }
};

int main(int argc, char* argv[]) { return 0; }
