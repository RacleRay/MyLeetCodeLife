#include "../../header.h"


class Solution {
public:
    int climbStairs(int n) {
        if (n <= 2) { return n; }

        vector<int> dp(2, 1);
        for (int i = 2; i <= n; i++) {
            dp[i % 2] = dp[(i - 1) % 2] + dp[(i - 2) % 2];
        }

        return dp[n % 2];
    }

    int climbStairs2(int n) {
        if (n <= 2) { return n; }

        int pre2 = 1, pre1 = 2, cur;

        for (int i = 2; i < n; i++) {
            cur = pre1 + pre2;
            pre2 = pre1;
            pre1 = cur;
        }

        return cur;
    }
};