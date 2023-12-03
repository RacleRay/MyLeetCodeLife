#include <iostream>
#include <vector>
#include <queue>


using namespace std;

class Solution {
public:
    int shortestBridge(vector<vector<int>>& grid) {
        queue<std::pair<int, int>> pqueue;
        int nrow = grid.size(), ncol = grid[0].size();

        bool fflag = false;
        for (int i = 0; i < nrow; ++i) {
            if (fflag) break;
            for (int j = 0; j < ncol; ++j) {
                if (grid[i][j] == 1) {
                    // 因为可能存在多个1相连的岛屿，所以这里的dfs是没问题的
                    dfs(grid, pqueue, i, j, nrow, ncol);
                    fflag = true;
                    break;
                }
            }
        }

        // bfs find next.
        int level = 0;
        int x = 0, y = 0;
        while (!pqueue.empty()) {
            ++level;
            int npoint = pqueue.size();
            while (npoint--) {
                pair<int, int> pfront = pqueue.front();
                pqueue.pop();
                int r = pfront.first, c = pfront.second;
                for (int i = 0; i < 4; ++i) {
                    x = r + direction[i];
                    y = c + direction[i + 1];
                    if (x < 0 || x >= nrow || y < 0 || y >= ncol) continue;
                    
                    if (grid[x][y] == 2) {
                        continue;
                    } else if (grid[x][y] == 1) {
                        return level;
                    }
                    pqueue.push({x, y});
                    grid[x][y] = 2;
                }
            }
        }

        return level;
    }


    void dfs(vector<vector<int>>& grid, queue<pair<int, int>>& que, \
        int i, int j, int nrow, int ncol) {
        if (i < 0 || i >= nrow || j < 0 || j >= ncol || grid[i][j] == 2) {
            return;
        }

        if (grid[i][j] == 0) {
            que.push({i, j});
            return;
        }

        grid[i][j] = 2;
        dfs(grid, que, i + 1, j, nrow, ncol);
        dfs(grid, que, i - 1, j, nrow, ncol);
        dfs(grid, que, i, j + 1, nrow, ncol);
        dfs(grid, que, i, j - 1, nrow, ncol);
    }

private:
    vector<int> direction {-1, 0, 1, 0, -1};
};


int main() {
    vector<vector<int>> in = {{0,1},{1,0}};

    Solution sl = Solution();
    sl.shortestBridge(in);

    return 0;
}