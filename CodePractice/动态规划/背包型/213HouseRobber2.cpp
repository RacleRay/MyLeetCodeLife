#include "../../header.h"

class Solution {
public:
    int rob(vector<int>& nums) {
        size_t length = nums.size();

        if (length == 1) {
            return nums[0];
        }
        if (length == 2) {
            return max(nums[0], nums[1]);
        }

        return max(rob_range(nums, 0, length - 2), rob_range(nums, 1, length - 1));
    }

    int rob_range(vector<int>& nums, int start, int end) {
        int first = nums.at(start), second = max(nums.at(start), nums.at(start + 1));
        for (int i = start + 2; i < end; ++i) {
            int tmp = second;
            second = max(second, first + nums.at(i)); // 偷了前一个，偷了前前一个+当前这个
            first = tmp; // 前前一个前移
        }
        return second;
    }
};