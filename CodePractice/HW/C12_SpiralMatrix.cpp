#include <iostream>
#include <vector>
#include <cmath>


using namespace std;

int main() {
    int n, nrow;
    cin >> n >> nrow;

    int ncol = std::ceil((double)n / nrow);

    std::vector<std::vector<int>> matrix(nrow, std::vector<int>(ncol, 0));

    int num = 1;
    int top = 0, bottom = nrow - 1, left = 0, right = ncol - 1;
    while (num <= n) {
        for (int i = left; i <= right && num <= n; i++) {
            matrix[top][i] = num++;
        }
        top++;

        for (int i = top; i <= bottom && num <= n; i++) {
            matrix[i][right] = num++;
        }
        right--;

        for (int i = right; i >= left && num <= n; i--) {
            matrix[bottom][i] = num++;
        }
        bottom--;

        for (int i = bottom; i >= top && num <= n; i--) {
            matrix[i][left] = num++;
        }
        left++;
    }

    for (int i = 0; i < nrow; i++) {
        for (int j = 0; j < ncol; j++) {
            if (matrix[i][j] == 0) {
                std::cout << '*';
            } else {
                std::cout << matrix[i][j];
            }

            if (j != ncol - 1) {
                std::cout << ' ';
            }
        }
        std::cout << '\n';
    }

    return 0;
}