#include "../../header.h"


class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        int n = nums.size();
        if (n < 3) return 0;

        vector<int> dp(n, 0);
        for (size_t i = 2; i < n; i++) {
            // 以i结尾满足等差定义
            if (nums[i] - nums[i - 1] == nums[i - 1] - nums[i - 2]) {
                dp[i] = dp[i - 1] + 1;
            }
        }

        return accumulate(dp.begin(), dp.end(), 0);
    }
};