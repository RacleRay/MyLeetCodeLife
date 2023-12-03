#include "../../header.h"


class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if (!nums.size()) { return 0; }
        if (nums.size() == 1) { return nums[0]; }

        size_t n = nums.size();
        std::vector<int> dp(n + 1, 0);
        int res = INT_MIN;

        for (size_t i = 1; i <= n; ++i) {
            dp[i] = max(nums.at(i) + dp[i - 1], nums.at(i));
            res = max(dp[i], res);
        }

        return res;
    }

    int maxSubArray2(vector<int>& nums) {
        size_t n = nums.size();

        if (!n) { return 0; }
        if (n == 1) { return nums[0]; }

        int pre = nums[0], res = nums[0];

        for (size_t i = 1; i < n; ++i) {
            pre = max(nums.at(i) + pre, nums.at(i));
            res = max(pre, res);
        }

        return res;
    }
};