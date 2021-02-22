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
    int cuttingRope(int n)
    {
        if (n == 2)
            return 1;
        if (n == 3)
            return 2;
        int x = n % 3, y = n / 3;
        if (x == 0)
            return pow(3, y);
        else if (x == 1)
            return 2 * 2 * pow(3, y - 1);
        else
            return 2 * pow(3, y);
    }

    int cuttingRope(int n)
    {
        if (n == 2)
            return 1;
        if (n == 3)
            return 2;
        int res = 1;
        // long res = 1;
        while (n > 4)
        {
            res *= 3;
            // res %= 1000000007;
            n -= 3;
        }
        res *= n;
        // res %= 1000000007;
        return res;
    }

    int cuttingRope(int n)
    {
        if (n == 2)
            return 1;
        if (n == 3)
            return 2;

        int curMax = -1;
        vector<int> ans(n + 1, 0);
        // 最小单元，不再切分
        ans[1] = 1;
        ans[2] = 2;
        ans[3] = 3;
        for (int i = 4; i <= n; i++)
        {
            for (int j = 1; j <= i / 2; j++)
            { // 一个数划分为两个数
                curMax = max(curMax, ans[j] * ans[i - j]);
                ans[i] = curMax;
            }
        }
        return ans[n];
    }
};