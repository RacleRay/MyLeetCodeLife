#include <iostream>
#include <vector>


using namespace std;


int countOnes(int w, int h, int x, int y, int sx, int sy, int t, vector<vector<int>>& matrix) {
    int count = matrix[y][x];
    while (t-- > 0) {
        x += sx;
        y += sy;

        if (x < 0) {
            x = 1;
            sx = -sx;
        } else if (x >= w) {
            x = w - 2;
            sx = -sx;
        }

        if (y < 0) {
            y = 1;
            sy = -sy;
        } else if (y >= h) {
            y = h - 2;
            sy = -sy;
        }

        count += matrix[y][x];
    }

    return count;
}


int main() {
    int w, h, x, y, sx, sy, t;
    cin >> w >> h >> x >> y >> sx >> sy >> t;

    vector<vector<int>> matrix(h, vector<int>(w));

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            char ch;
            cin >> ch;
            matrix[i][j] = ch - '0';
        }
    }

    cout << countOnes(w, h, x, y, sx, sy, t, matrix) << endl;
    return 0;
}