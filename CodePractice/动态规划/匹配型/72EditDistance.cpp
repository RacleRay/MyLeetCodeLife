#include "../../header.h"


class Solution {
public:
    int minDistance(string word1, string word2) {
        int w1_len = word1.size(), w2_len = word2.size();
        vector<vector<int>> dp(w1_len + 1, vector<int>(w2_len + 1, 0));
        for (int i = 0; i <= w1_len; i++) {
            for (int j = 0; j <= w2_len; j++) {
                if (i == 0) {
                    dp[i][j] = j;
                } else if (j == 0) {
                    dp[i][j] = i;
                } else {
                    dp[i][j] = min(
                        dp[i - 1][j - 1] + (word1[i - 1] == word2[j - 1] ? 0 : 1),
                        min(dp[i - 1][j] + 1, dp[i][j - 1] + 1)
                    );
                }
            }
        }

        return dp[w1_len][w2_len];
    }
};