#include <iostream>
#include <vector>


using namespace std;

// https://fcqian.blog.csdn.net/article/details/135085069

class Solution {
public:
    vector<vector<int>> generate(int n, int m) {
        int cols = static_cast<int>(n / m) + 1;
        int rows = m;

        vector<vector<int>> result;
        for (int i = 0; i < rows; ++i) {
            vector<int> tmp(cols, -1);
            result.push_back(std::move(tmp));
        }

        int steps = 1;
        int x = 0, y = 0;
        while (steps <= n) {
            while (y < cols && result[x][y] == -1 && steps <= n) {
                result[x][y] = steps++;
                y++;
            }
            y -= 1;  // fix
            x += 1;  // next row

            while (x < rows && result[x][y] == -1 && steps <= n) {
                result[x][y] = steps++;
                x++;
            }
            x -= 1;
            y -= 1;  // next col 

            while (y >= 0 && result[x][y] == -1 && steps <= n) {
                result[x][y] = steps++;
                y--;
            }
            y += 1;  // fix
            x -= 1;  // next row

            while (x >= 0 && result[x][y] == -1 && steps <= n) {
                result[x][y] = steps++;
                x--;
            }       
            x += 1;
            y += 1;  // next col
        }

        return result;
    }

};


int main() {
    int n, m;
    cin >> n >> m;

    auto res = Solution().generate(n, m);
    for (auto& row : res) {
        for (int i = 0; i < row.size(); i++) {
            int elem = row[i];
            if (elem == -1) {
                cout << '*';
            } else {
                cout << elem;
            }

            if (i != (row.size() - 1) ) {
                cout << ' ';
            }
        }
        cout << endl;
    }

    return 0;
}