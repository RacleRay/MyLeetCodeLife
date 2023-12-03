#include "../../header.h"


class Solution {
public:
    int numDecodings(string s) {
        int len = s.length();
        if (len == 0) return 0;

        if (s[0] == '0') return 0;
        
        if (len == 1) return 1;

        int prev = s[0] - '0';
        vector<int> dp(len + 1, 1);
        for (int i = 2; i <= len; i++) {
            int cur = s[i - 1] - '0';
            // 00  or  30
            if ((prev == 0 || prev > 2) && cur == 0) {
                return 0;
            }

            // prev 和 cur 可能组合
            if ((prev == 1) || (prev == 2 && cur <= 6)) {
                if (cur == 0) {  // cur 必须和 prev 组合
                    dp[i] = dp[i - 2];
                } else {
                    dp[i] = dp[i - 1] + dp[i - 2];  // cur 可以和 prev 组合，或者单独成一个
                }
            } else {  // 没有组合选择，只能单独一个
                dp[i] = dp[i - 1];
            }

            prev = cur;
        }

        return dp[len];
    }
};
