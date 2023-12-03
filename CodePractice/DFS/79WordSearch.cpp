#include <iostream>
#include <vector>


using namespace std;


class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        if (board.empty()) return false;
        int  nrow = board.size(), ncol = board[0].size();
        bool find = false;

        vector<vector<bool>> visited(nrow, vector<bool>(ncol, false));

        for (int i = 0; i < nrow; ++i) {
            for (int j = 0; j < ncol; ++j) {
                backstracking(i, j, board, find, word, visited, 0);
            }
        }

        return find;
    }

    void backstracking(int i, int j, vector<vector<char>>& board, bool& find,
                       string& word, vector<vector<bool>>& visited, int idx) {
        // didn`t find
        if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size()) {
            return;
        }
        // visited or illegal or already found
        if (visited[i][j] || board[i][j] != word[idx] || find) {
            return;
        }
        // fit word
        if (idx == word.size() - 1) {
            find = true;
            return;
        }

        // travaling
        visited[i][j] = true;

        backstracking(i, j + 1, board, find, word, visited, idx + 1);
        backstracking(i, j - 1, board, find, word, visited, idx + 1);
        backstracking(i + 1, j, board, find, word, visited, idx + 1);
        backstracking(i - 1, j, board, find, word, visited, idx + 1);

        // backstrack
        visited[i][j] = false;
    }
};