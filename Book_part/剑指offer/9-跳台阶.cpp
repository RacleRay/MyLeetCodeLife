#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <stack>
#include <unordered_map>

using namespace std;

class Solution
{
public:
    int numWays(int n)
    {
        if (n == 0)
            return 1;
        if (n <= 2)
            return n;
        int first = 1, second = 2, total = -1;
        for (int i = 3; i <= n; i++)
        {
            total = (first + second) % 1000000007;
            first = second;
            second = total;
        }
        return total;
    }
};