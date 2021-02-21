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
    int rows, cols, thred;

    int movingCount(int m, int n, int k)
    {
        vector<vector<bool>> visit(m, vector<bool>(n, false));
        rows = m;
        cols = n;
        thred = k;
        return recursionCount(0, 0, visit);
    }

    int recursionCount(int i, int j, vector<vector<bool>> &visit)
    {
        if (i >= rows || j >= cols || !valid(i, j) || visit[i][j] == true)
            return 0;
        visit[i][j] = true;
        return recursionCount(i + 1, j, visit) + recursionCount(i, j + 1, visit) + 1;
    }

    bool valid(int i, int j)
    {
        int sum = 0;
        while (i > 0)
        {
            sum += i % 10;
            i /= 10;
        }
        while (j > 0)
        {
            sum += j % 10;
            j /= 10;
        }
        return sum <= thred;
    }
};