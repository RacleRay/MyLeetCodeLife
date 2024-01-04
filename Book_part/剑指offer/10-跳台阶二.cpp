#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <stack>
#include <unordered_map>
#include <cmath>

using namespace std;


// 一只青蛙一次可以跳上1级台阶，也可以跳上2级……它也可以跳上n级
class Solution
{
public:
    // 一步可以跳 1 到 n 级，那么选择跳的级数后，每种情况是互斥的，不会同时发生
    // 所以 f(n) = f(n-1) + f(n-2) + ... + f(1) + f(0)
    // f(n) = 2 * f(n-1)
    // f(n) = 2^(n-1)
    int numWays(int n)
    {
        if (n==0) return 1;
        if (n==1) return 1;
        return pow(2, n-1);
    }
};