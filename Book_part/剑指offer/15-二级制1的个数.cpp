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
    int hammingWeight(uint32_t n)
    {
        bitset<32> bits(n);
        return bits.count();
    }

    int hammingWeight(uint32_t n)
    {
        int res = 0;
        while (n > 0)
        {
            n = n & (n - 1); //最右边一个1变成0
            res++;
        }
        return res;
    }
};