#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <stack>
#include <unordered_map>
#include <cmath>
#include <bitset>

using namespace std;

class Solution
{
public:
    double myPow(double x, int n)
    {
        if (n == 0)
            return 1.0;
        if (x == 0.0)
            return 0.0;
        double res = 1.0;
        long exp = n; // 注意是long
        if (n < 0)
            exp *= -1;
        
        while (exp != 0)
        {
            if (((exp & 1) == 1))
            {
                res *= x;
            }
            x *= x;
            exp >>= 1;
        }
        return n < 0 ? 1.0 / res : res;
    }
};
