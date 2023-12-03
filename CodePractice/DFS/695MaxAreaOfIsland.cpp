#include <stack>
#include <vector>
#include <iostream>


using namespace std;

class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int nrows    = grid.size();
        int ncols    = nrows ? grid[0].size() : 0;
        int cur_area = 0, max_area = 0;

        for (int row = 0; row < nrows; ++row) {
            for (int col = 0; col < ncols; ++col) {
                if (!grid[row][col]) continue;

                grid[row][col] = 0;
                stack<pair<int, int>> island;
                island.push({row, col});
                cur_area = 1;

                while (!island.empty()) {
                    auto tmp = island.top();
                    int  x = tmp.first, y = tmp.second;
                    island.pop();
                    for (int di = 0; di < 4; ++di) {
                        int nx = x + direction[di], ny = y + direction[di + 1];
                        if (nx >= 0 && nx < nrows && ny >= 0 && ny < ncols
                            && grid[nx][ny] == 1) {
                            grid[nx][ny] = 0;
                            ++cur_area;
                            island.push({nx, ny});
                        }
                    }
                }

                max_area = max(max_area, cur_area);
            }
        }

        return max_area;
    }
    
    int dfs(vector<vector<int>>& grid, int r, int c) {
        if (grid[r][c] == 0) return 0;
        grid[r][c] = 0;

        int x, y, area = 1;
        for (int i = 0; i < 4; ++i) {
            x = r + direction[i], y = c + direction[i + 1];
            if (x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size())
                area += dfs(grid, x, y);
        }

        return area;
    }

private:
    vector<int> direction{-1, 0, 1, 0, -1};  // 6
};


int main() {
    Solution sl = Solution();
    
    vector<vector<int>> in {{0, 1, 0, 1}, {0, 1, 0, 0}, {0, 0, 0, 0}};
    int res = sl.maxAreaOfIsland(in);

    std::cout << res << std::endl;

    return 0;

}