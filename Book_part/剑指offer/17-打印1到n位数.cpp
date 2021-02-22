#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <stack>
#include <unordered_map>
#include <cmath>
#include <bitset>
#include <stdio.h>
#include <string.h>

using namespace std;

class Solution
{
public:
    vector<int> printNumbers(int n)
    {
        vector<int> res;
        char *str = new char[n + 1];
        dfs(0, n, res, str);
        return res;
    }

    void dfs(int x, int n, vector<int> &res, char *str)
    {
        if (x == n)
        {
            int cur = 0;
            // 转为int，当越界时，应当考虑输出字符串
            for (int i = 0; i < n; i++)
            {
                cur = cur * 10 + forward<int>(str[i]);
            }
            if (cur != 0)
                res.push_back(cur);
            return;
        }
        for (int i = 0; i <= 9; i++)
        {
            str[x] = forward<char>(i);
            dfs(x+1, n, res, str);
        }
    }
};