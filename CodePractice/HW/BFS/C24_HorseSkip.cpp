#include <climits>
#include <iostream>
#include <queue>
#include <set>
#include <vector>
#include <tuple>


using namespace std;


int nrow, ncol;
vector<vector<char>> board;
vector<tuple<int, int, int>> horses;


int bfs() {
    vector<pair<int, int>> dirs = {{-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}};

    int min_steps = INT_MAX;
    for (int i = 0; i < nrow; i++) {
        for (int j = 0; j < ncol; j++) {
            int total_steps = 0;
            
            // 是否所有马可达当前位置
            bool possible = true;

            for (auto& horse : horses) {
                queue<tuple<int, int, int>> que;
                set<string> visited;

                int x, y, max_steps;
                tie(x, y, max_steps) = horse;

                que.push({x, y, 0});
                visited.insert(to_string(x) + "," + to_string(y));

                bool found = false;  // (i, j)

                while (!que.empty() && possible) {
                    tuple<int, int, int> cur = que.front();
                    que.pop();
                    int cx, cy, cs;
                    tie(cx, cy, cs) = cur;
                    if (cx == i && cy == j) {
                       total_steps += cs;
                       found += true; 
                       break;
                    }

                    for (auto& dir : dirs) {
                        int nx = cx + dir.first;
                        int ny = cy + dir.second;

                        if (nx < 0 || nx >= nrow || ny < 0 || ny >= ncol 
                            || visited.count(to_string(nx) + "," + to_string(ny)) || cs >= max_steps) 
                        {
                            continue;
                        }

                        que.push({nx, ny, cs + 1});
                        visited.insert(to_string(nx) + "," + to_string(ny));
                    }
                }

                if (!found) {
                    possible = false;
                }
            }

            if (possible) {
                min_steps = min(min_steps, total_steps);
            }
        }
    }

    return min_steps == INT_MAX ? -1 : min_steps;
}


int main() {
    cin >> nrow >> ncol;

    board.resize(nrow, vector<char>(ncol));

    for (int i = 0; i < nrow; i++) {
        for (int j = 0; j < ncol; j++) {
            cin >> board[i][j];
            if (board[i][j] != '.') {
                horses.emplace_back(i, j, board[i][j] - '0');
            }
        }
    }

    // bfs
    cout << bfs() << endl;

    return 0;
}
