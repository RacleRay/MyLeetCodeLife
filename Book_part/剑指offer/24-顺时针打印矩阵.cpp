#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <stack>
#include <unordered_map>
#include <cmath>
#include <bitset>
#include <stdio.h>
#include <string.h>

using namespace std;

class Solution
{
public:
    vector<int> spiralOrder(vector<vector<int>> &matrix)
    {
        if (matrix.size() == 0 || matrix[0].size() == 0)
            return vector<int>();

        int left = 0, right = matrix[0].size() - 1, top = 0, bottom = matrix.size() - 1;

        vector<int> res;
        res.reserve(matrix[0].size() * matrix.size());

        while (left <= right && top <= bottom)
        {
            for (int i = left; i <= right; i++)
            {
                res.push_back(matrix[top][i]);
            }
            if (++top > bottom)
                break;
            for (int i = top; i <= bottom; i++)
            {
                res.push_back(matrix[i][right]);
            }
            if (--right < left)
                break;
            for (int i = right; i >= left; --i)
            {
                res.push_back(matrix[bottom][i]);
            }
            if (--bottom < top)
                break;
            for (int i = bottom; i >= top; --i)
            {
                res.push_back(matrix[i][left]);
            }
            if (++left > right)
                break;
        }

        return res;
    }
};