#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <stack>
#include <unordered_map>
#include <cmath>

using namespace std;

class Solution
{
public:
    bool exist(vector<vector<char>> &board, string word)
    {
        for (int i = 0; i < board.size(); i++)
        {
            for (int j = 0; j < board[0].size(); j++)
            {
                if (dfs(board, word, i, j, 0)) return true;
            }
        }
        return false;
    }

    bool dfs(vector<vector<char>> &board, string& word, int i, int j, int k)
    {
        if (i >= board.size() || j >= board[0].size() || i < 0 || j < 0 || board[i][j] != word[k])
            return false;
        if (k == word.length() - 1)
            return true;
        else
        {
            board[i][j] = '\0';
            bool recursion = dfs(board, word, i + 1, j, k + 1) || dfs(board, word, i, j + 1, k + 1) ||
                             dfs(board, word, i - 1, j, k + 1) || dfs(board, word, i, j - 1, k + 1);
            board[i][j] = word[k];
            return recursion;
        }
    }
};