#include "../../header.h"


class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int nrow = grid.size(), ncol = grid[0].size();
        vector<vector<int>> dp(nrow, vector<int>(ncol, 0));

        for (size_t i = 0; i < nrow; i++) {
            for (size_t j = 0; j < ncol; j++) {
                if (i == 0 && j == 0) {
                    dp[i][j] = grid[i][j];
                } else if (i == 0) {
                    dp[i][j] = dp[i][j - 1] + grid[i][j];
                } else if (j == 0) {
                    dp[i][j] = dp[i - 1][j] + grid[i][j];
                } else {
                    dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
                }
            }
        }

        return dp[nrow - 1][ncol - 1];
    }

    int minPathSum2(vector<vector<int>>& grid) {
        // 状态压缩
        /**
         * 因为 dp 矩阵的每一个值只和左边和上面的值相关，我们可以使用空间压缩将 dp 数组压缩为
         * 一维。对于第 i 行，在遍历到第 j 列的时候，因为第j-1列已经更新过了，所以dp[j-1]代表dp[i][j-1] 的值；
         * 而 dp[j] 待更新，当前存储的值是在第 i-1 行的时候计算的，所以代表 dp[i-1][j] 的值
         */

        int nrow = grid.size(), ncol = grid[0].size();
        vector<int> dp(ncol, 0);
        
        for (size_t i = 0; i < nrow; i++) {
            for (size_t j = 0; j < ncol; j++) {
                if (i == 0 && j == 0) {
                    dp[j] = grid[i][j];
                } else if (i == 0) {
                    dp[j] = dp[j - 1] + grid[i][j];
                } else if (j == 0) {
                    dp[j] = dp[j] + grid[i][j];
                } else {
                    dp[j] = min(dp[j - 1], dp[j]) + grid[i][j];
                }
            }
        }

        return dp[ncol - 1];
    }
};