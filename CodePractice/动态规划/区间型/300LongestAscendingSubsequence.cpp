#include "../../header.h"


class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int max_length = 0, n = nums.size();
        if (n <= 1) { return n; }

        vector<int> dp(n, 1);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            max_length = max(max_length, dp[i]);
        }

        return max_length;
    }

    int lengthOfLIS2(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) { return n; }

        vector<int> dp;
        dp.push_back(nums[0]);  // 当前递增序列
        for (int i = 1; i < n; i++) {
            if (nums[i] > dp.back()) {
                dp.push_back(nums[i]);
            } else {
                // 长的递增序列必定满足这个条件
                auto iter = lower_bound(dp.begin(), dp.end(), nums[i]);
                *iter = nums[i];
            }
        }

        return dp.size();
    }
};
