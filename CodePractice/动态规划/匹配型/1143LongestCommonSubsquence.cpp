#include "../../header.h"


class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int len1 = text1.size(), len2 = text2.size();

        vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));

        // 这里的 dp , 定义为 到串1的i 和串2的j 为止，最长公共子序列的长度
        // 不必一定以 i 或者 j 结尾
        // 状态转化可以直接 dp[i - 1][j - 1] + 1 
        // 另一种 dp , 定义为 以 i 结尾。计算结果时，需要比较每个位置的结果
        // 也就多了一个 max 比较
        for (int i = 1; i <= len1; i++) {
            for (int j = 1; j <= len2; j++) {
                if (text1[i - 1] == text2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

        return dp[len1][len2];
    }
};
