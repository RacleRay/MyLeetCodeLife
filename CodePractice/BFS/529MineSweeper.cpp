#include "../header.h"


class Solution {
public:
    using Coordinate = pair<int, int>;

    vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) {
        int nrow = board.size(), ncol = board[0].size();

        vector<vector<char>> visited(nrow, vector<char>(ncol, 0));
        int                  x = click[0], y = click[1];

        if (board[x][y] == 'M') {
            board[x][y] = 'X';
        }
        else if (board[x][y] == 'E') {
            Coordinate start = {x, y};
            bfs(board, visited, start, nrow, ncol);
        }

        return board;
    }

    void bfs(vector<vector<char>>& board, vector<vector<char>>& visited, Coordinate start, int nrow, int ncol) {
        std::queue<Coordinate> cor_queue;
        cor_queue.push(start);
        visited[start.first][start.second] = 1;

        while (!cor_queue.empty()) {
            Coordinate cor = cor_queue.front();
            cor_queue.pop();
            int x = cor.first, y = cor.second;
            int mine_count = 0;

            // stats the mine around
            for (auto dir: directions) {
                int nx = x + dir[0], ny = y + dir[1];
                if (nx < 0 || nx >= nrow || ny < 0 || ny >= ncol) {
                    continue;
                }
                if (board[nx][ny] == 'M') {
                    mine_count++;
                }
            }

            board[x][y] = mine_count == 0 ? 'B' : mine_count + '0';

            // find next
            for (auto dir: directions) {
                int nx = x + dir[0], ny = y + dir[1];
                if (nx < 0 || nx >= nrow || ny < 0 || ny >= ncol) {
                    continue;
                }

                // 想想扫雷游戏，一次点击，相邻的只有没有雷的情况下，可以发现一大片，且不用再遍历 'B' 边界
                if (visited[nx][ny] == 0 && mine_count == 0 && board[nx][ny] == 'E') {
                    cor_queue.emplace(nx, ny);
                    visited[nx][ny] = 1;
                }
            }
        }
    }

private:
    int directions[8][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {-1, 1}, {1, -1}, {-1, -1}, {1, 1}};
};