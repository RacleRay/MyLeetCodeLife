#include "../../header.h"


class Solution {
public:
    int numSquares(int n) {
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;

        // dp[i] 表示数字 i 最少可以由几个完全平方数相加 构成
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j * j <= i; j++) {
                dp[i] = min(dp[i], dp[i - j *j] + 1);
            }
        }

        return dp[n];
    }
};

