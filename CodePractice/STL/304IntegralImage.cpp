/*************************************************************************
    > File Name: 304IntegralImage.cpp
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time: 
 ************************************************************************/

#include <vector>

using namespace std;

class NumMatrix {
    vector<vector<int>> integral;

public:
    NumMatrix(vector<vector<int>>& matrix) {
        int n_row = matrix.size(), n_col = n_row > 0 ? matrix[0].size(): 0;

        integral = vector<vector<int>>(n_row + 1, vector<int>((n_col + 1), 0));

        // 注意这里的初始化顺序，完美契合计算公式的需要
        for (int i = 1; i <= n_row; ++i) {
            for (int j = 1; j <= n_col; ++j) {
                integral[i][j] = matrix[i - 1][j - 1] + integral[i - 1][j] + integral[i][j - 1] - integral[i - 1][j - 1];
            }
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        return integral[row2 + 1][col2 + 1] - integral[row2 + 1][col1] - integral[row1][col2 + 1] + integral[row1][col1];
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
 */
