#include "../../header.h"


class Solution {
public:
    int minDistance(string word1, string word2) {
        size_t nrow = word1.size() + 1, ncol = word2.size() + 1;
        vector<vector<int>> dp(nrow + 1, vector<int>(ncol, 0));

        // 假设每个字符串之前添加了一个虚拟的 空格
        for (int i = 0; i <= nrow; ++i) {
            dp[i][0] = 1;
        }
        for (int j = 0; j <= ncol; ++j) {
            dp[0][j] = 1;
        }

        for (int i = 1; i <= nrow; ++i) {
            for (int j = 1; j <= ncol; ++j) {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);
                }
            }
        }

        int max = dp[nrow][ncol] - 1;
        return nrow + ncol - 2 * max;
    }

    int minDistance2(string word1, string word2) {
        size_t nrow = word1.size() + 1, ncol = word2.size() + 1;
        vector<vector<int>> dp(nrow + 1, vector<int>(ncol + 1, 0));

        // 不带虚拟空格
        for (int i = 1; i <= nrow; i++) {
            for (int j = 1; j <= ncol; j++) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

        int max = dp[nrow][ncol];
        return nrow + ncol - 2 * max;
    }
};