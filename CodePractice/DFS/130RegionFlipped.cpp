#include <iostream>
#include <vector>


using namespace std;

// https://leetcode.cn/problems/surrounded-regions/
class Solution {
public:
    void solve(vector<vector<char>>& board) {
        if (!board.size() || !board[0].size()) return;

        int nrow = board.size();
        int ncol = board[0].size();

        for (int i = 0; i < ncol; ++i) {
            if (board[0][i] == 'O') dfs(board, 0, i, nrow, ncol);
            if (board[nrow - 1][i] == 'O') dfs(board, nrow - 1, i, nrow, ncol);
        }

        for (int i = 0; i < nrow; ++i) {
            if (board[i][0] == 'O') dfs(board, i, 0, nrow, ncol);
            if (board[i][ncol - 1] == 'O') dfs(board, i, ncol - 1, nrow, ncol);
        }

        for (int i = 0; i < nrow; ++i) {
            for (int j = 0; j < ncol; ++j) {
                // char& tmp = board[i][j];
                if (board[i][j] == 'O') board[i][j] = 'X';
                if (board[i][j] == 'B') board[i][j] = 'O';
            }
        }
    }

    void dfs(vector<vector<char>>& board, int i, int j, int nrow, int ncol) {
        board[i][j] = 'B';
        for (int di = 0; di < 4; ++di) {
            int x = i + directions[di];
            int y = j + directions[di + 1];
            if (x < 0 || y < 0 || x >= nrow || y >= ncol || board[x][y] != 'O') continue;
            dfs(board, x, y, nrow, ncol);
        }
    }

private:
    vector<int> directions {-1, 0, 1, 0, -1};
};


int main() {
    Solution sl = Solution();
    vector<vector<char>> in_ {{'X','O','X','O','X','O'},{'O','X','O','X','O','X'},{'X','O','X','O','X','O'},{'O','X','O','X','O','X'}};
    sl.solve(in_);
    return 0;
}