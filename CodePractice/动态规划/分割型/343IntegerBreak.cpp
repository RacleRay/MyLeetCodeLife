#include "../../header.h"


class Solution {
public:
    int integerBreak(int n) {
        std::vector<int> dp(n + 1, 0);

        int max_product = 0;
        for (int i = 2; i <= n; ++i) {
            max_product = 0;
            // start break
            for (int j = 1; j <= i / 2; ++j) {
                max_product = max(max_product, max(j * (i - j), j * dp[i - j]));
            }
            dp[i] = max_product;
        }

        return dp[n];
    }

    // 只会出现2 和 3 的字数拆分
    int integerBreak2(int n) {
        if (n <= 3) { return n - 1; }

        std::vector<int> dp(n + 1, 0);
        dp[2] = 1;
        for (int i = 3; i <= n; ++i) {
            dp[i] = max(max(2 * (i - 2), dp[i - 2] * 2),
                        max(3 * (i - 3), dp[i - 3] * 3));
        }

        return dp[n];
    }
};