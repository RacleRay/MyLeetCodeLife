
#include <iostream>
#include <string>
#include <vector>


using namespace std;

class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> ans;
        if (n == 0) return ans;

        vector<string> board(n, string(n, '.'));
        vector<bool> column(n, false);
        vector<bool> ldiag(2 * n - 1, false), rdiag(2 * n - 1, false);

        backstracking(n, 0, ans, board, column, ldiag, rdiag);

        return ans;
    }

    void backstracking(int n, int rpos, vector<vector<string>>& ans,
                       vector<string>& board, vector<bool>& column,
                       vector<bool>& ldiag, vector<bool>& rdiag) {
        if (rpos == n) {
            ans.push_back(board);
            return;
        }

        // travel columns
        for (int i = 0; i < n; ++i) {
            // check if col i is legal.
            if (column[i] || ldiag[n - 1 - rpos + i] || rdiag[n - 1 - rpos + i) {
                continue;
            }

            // current line state
            board[rpos][i] = 'Q';
            column[i] = ldiag[n - 1 - rpos + 1] = rdiag[n - 1 - rpos + i] = true;

            // recurrsion
            backstracking(n, rpos + 1, ans, board, column, ldiag, rdiag);

            // backstrack
            board[rpos][i] = '.';
            column[i] = ldiag[n - 1 - rpos + 1] = rdiag[n - 1 - rpos + i] = false;
        }
    }
};


int main() {
    Solution sl = Solution();

    sl.solveNQueens(4);

    return 0;
}