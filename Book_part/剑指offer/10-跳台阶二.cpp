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
    int numWays(int n)
    {
        if (n==0) return 1;
        if (n==1) return 1;
        return pow(2, n-1);
    }
};