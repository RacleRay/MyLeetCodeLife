#include "../header.h"


class Solution {
public:
    int closedIsland(vector<vector<int>>& grid) {
        int nrow = grid.size(), ncol = grid[0].size();

        if (nrow < 3 || ncol < 3) {
            return 0;
        }

        for (int i = 0; i < nrow; ++i) {
            int step = (i == 0 || i == nrow - 1) ? 1 : ncol - 1;
            for (int j = 0; j < ncol; j += step) {
                dfs(grid, i, j);
            }
        }

        int ans = 0;
        for (int i = 1; i < nrow - 1; ++i) {
            for (int j = 1; j < ncol - 1; ++j) {
                if (grid[i][j] == 0) {
                    ans++;
                    dfs(grid, i, j);
                }
            }
        }

        return ans;
    }

    void dfs(vector<vector<int>>& grid, int i, int j) {
        if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size() || grid[i][j]) {
            return;
        }

        grid[i][j] = 1;
        dfs(grid, i - 1, j);
        dfs(grid, i + 1, j);
        dfs(grid, i, j - 1);
        dfs(grid, i, j + 1);
    }
};