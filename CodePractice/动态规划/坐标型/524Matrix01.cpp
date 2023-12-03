#include "../../header.h"


class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        if (mat.empty()) { return {}; }

        int nrow = mat.size(), ncol = mat[0].size();
        vector<vector<int>> dp(nrow, vector<int>(ncol, INT_MAX - 1));

        for (size_t i = 0; i < nrow; i++) {
            for (size_t j = 0; j < ncol; j++) {
                if (mat[i][j] == 0) {
                    dp[i][j] = 0;
                } else {
                    if (j > 0) {
                        dp[i][j] = min(dp[i][j], dp[i][j - 1] + 1);
                    }
                    if (i > 0) {
                        dp[i][j] = min(dp[i][j], dp[i - 1][j] + 1);
                    }
                }
            }
        }

        // 这里的 -- ，如果用的是 size_t 那么就会下溢出
        for (int i = nrow - 1; i >= 0; i--) {
            for (int j = ncol - 1; j >= 0; j--) {
                if (mat[i][j] == 0) { continue; }
                if (j < ncol - 1) {
                    dp[i][j] = min(dp[i][j], dp[i][j + 1] + 1);
                }
                if (i < nrow - 1) {
                    dp[i][j] = min(dp[i][j], dp[i + 1][j] + 1);
                }
            }
        }

        return dp;
    }
};