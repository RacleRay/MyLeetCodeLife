#include "../../header.h"


class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) { 
            return 0;
        }

        int nrow = matrix.size(), ncol = matrix[0].size();
        // + 1 是为了方便状态转换计算
        vector<vector<int>> dp(nrow + 1, vector<int>(ncol + 1, 0));

        int max_side = 0;
        for (size_t i = 1; i <= nrow; i++) {
            for (size_t j = 1; j <= ncol; j++) {
                if (matrix[i - 1][j - 1] == '1') {
                    dp[i][j] = min(dp[i - 1][j], min(dp[i][j - 1], dp[i - 1][j - 1])) + 1;
                }
                max_side = max(max_side, dp[i][j]);
            }
        }

        return max_side * max_side;
    }

    int maximalSquare2(vector<vector<char>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) { 
            return 0;
        }

        int nrow = matrix.size(), ncol = matrix[0].size();
        vector<vector<int>> dp(nrow, vector<int>(ncol, 0));

        int max_side = 0;
        for (size_t i = 0; i < nrow; i++) {
            for (size_t j = 0; j < ncol; j++) {
                if (i == 0 || j == 0) {
                    dp[i][j] = matrix[i][j] - '0';
                } else if (matrix[i][j] == '1') {
                    dp[i][j] = min(dp[i - 1][j], min(dp[i][j - 1], dp[i - 1][j - 1])) + 1;
                }
                max_side = max(max_side, dp[i][j]);
            }
        }

        return max_side * max_side;
    }
};