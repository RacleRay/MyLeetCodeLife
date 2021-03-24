#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <stack>
#include <set>
#include <unordered_map>
#include <queue>
#include <functional>
#include <cmath>
#include <bitset>
#include <stdio.h>
#include <string.h>
#include <limits.h>

using namespace std;

class Solution
{
public:
    int nthUglyNumber(int n)
    {
        if (n < 7)
            return n;

        vector<int> res(n, 0);
        res[0] = 1;

        int idxtwo = 0;
        int idxthree = 0;
        int idxfive = 0;
        // int minx = 0;
        for (int i = 1; i < n; i++)
        {
            int minx = min(min(res[idxtwo] * 2, res[idxthree] * 3), res[idxfive] * 5);
            if (minx == res[idxtwo] * 2)
                idxtwo++;
            else if (minx == res[idxthree] * 3)
                idxthree++;
            else if (minx == res[idxfive] * 5)
                idxfive++;
            res[i] = minx;
        }

        return res[n - 1];
    }
};

int main()
{
    Solution s = Solution();

    s.nthUglyNumber(10);
}