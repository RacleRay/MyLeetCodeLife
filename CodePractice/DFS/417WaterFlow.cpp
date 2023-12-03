#include <iostream>
#include <vector>
#include <stack>

// https://leetcode.com/problems/pacific-atlantic-water-flow/

using namespace std;

class Solution {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        vector<vector<int>> res;

        int nrow = heights.size(), ncol = heights[0].size();
        vector<vector<bool>> reach_from_p(nrow, vector<bool>(ncol, false));
        vector<vector<bool>> reach_from_a(nrow, vector<bool>(ncol, false));

        for (int i = 0; i < nrow; ++i) {
            // p from (i, 0)
            dfs(heights, i, 0, reach_from_p);
            // a from (i, ncol - 1)
            dfs(heights, i, ncol - 1, reach_from_a);
        }

        for (int j = 0; j < ncol; ++j) {
            dfs(heights, 0, j, reach_from_p);
            dfs(heights, nrow - 1, j, reach_from_a);
        }

        for (int i = 0; i < nrow; ++i) {
            for (int j = 0; j < ncol; ++j) {
                if (reach_from_a[i][j] && reach_from_p[i][j])
                    res.push_back({i, j});
            }
        }

        return res;
    }

    void dfs(vector<vector<int>>& heights, int r, int c, vector<vector<bool>>& reach_mat) {
        if (reach_mat[r][c] == true) return;

        reach_mat[r][c] = true;
        for (int i = 0; i < 4; ++i) {
            int x = r + direction[i], y = c + direction[i + 1];
            if (x >= 0 && x < heights.size() && \
                y >= 0 && y < heights[0].size() && \
                heights[r][c] <= heights[x][y]) 
            {
                dfs(heights, x, y, reach_mat);
            }
        }
    }

private:
    vector<int> direction{-1, 0, 1, 0, -1};  // 6
};