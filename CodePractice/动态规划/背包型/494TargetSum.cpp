#include "../../header.h"


class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if ((target + sum) % 2 == 1 || abs(target) > sum) return 0;
        int bag_target = (target + sum) / 2;
        size_t n = nums.size();
        // vector<vector<int>> dp(n + 1, vector<int>(bag_target + 1, 0));
        // for (size_t i = 0; i <= n; i++) {
        //     dp[i][0] = 1;
        // }
        vector<int> dp(bag_target + 1, 0);
        dp[0] = 1;

        // dp[i][j] 表示前 i 个数，其和为 j 是否可行
        // for (size_t i = 1; i <= n; i++) {
            // for (size_t j = 0; j <= bag_target; j++) {
            //     if (j < nums[i - 1]) {  // 和不可能为 J
            //         dp[i][j] = dp[i - 1][j];
            //     } else {  // 不算当前数，或者算当前数
            //         dp[i][j] = dp[i - 1][j] + dp[i - 1][j - nums[i - 1]];
            //     }
            // }
        for (size_t i = 0; i < n; i++) {
            for (int j = bag_target; j >= nums[i]; j--) {
                dp[j] = dp[j] + dp[j - nums[i]];
            }
        }

        // return dp[n][bag_target]; 
        return dp[bag_target];
    }
};


int main() {
    vector<int> nums = {1, 0};

    int target = 1;

    Solution s;
    s.findTargetSumWays(nums, target);

    return 0;
}
