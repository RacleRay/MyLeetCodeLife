
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Solution
{
public:
    int fib(int n)
    {
        if (n == 0)
            return 0;
        if (n == 1)
            return 1;
        int first = 0, second = 1, third = 1;
        // 1000000007 是最小的十位质数。模1000000007，可以保证值永远在int的范围内。只考虑正确性，而不用考虑结果的值
        for (int i = 2; i <= n; ++i)
        {
            third = (first + second) % 1000000007;
            first = second;
            second = third;
        }
        return third;
    }
};