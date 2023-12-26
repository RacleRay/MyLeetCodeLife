#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    bool findNumberIn2DArray(vector<vector<int>> &matrix, int target)
    {
        if (matrix.empty() || matrix[0].empty())
            return false;
        int col = matrix[0].size();
        int row = matrix.size();

        // 找个大小变化相反的位置，要么向小要么向大
        int colIndex = col - 1;
        int rowIndex = 0;
        while (colIndex >= 0 && rowIndex < row)
        {
            if (matrix[rowIndex][colIndex] > target)
                colIndex--;
            else if (matrix[rowIndex][colIndex] < target)
                rowIndex++;
            else
                return true;
        }
        return false;
    }

    bool findNumberIn2DArray2(vector<vector<int>> &matrix, int target)
    {
        if (matrix.empty() || matrix[0].empty())
            return false;

        for (int i = 0; i < matrix.size(); i++)
        {
            int start = 0;
            int end = matrix[0].size();
            while (start < end)
            {
                int mid = start + (end - start) / 2;
                if (matrix[i][mid] == target)
                    return true;
                else if (matrix[i][mid] > target)
                    end = mid;
                else
                    start = mid + 1;
            }
        }
        return false;
    }
};