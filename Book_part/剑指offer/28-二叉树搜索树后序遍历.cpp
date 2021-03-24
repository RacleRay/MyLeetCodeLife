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
#include <limits.h>

using namespace std;

class Solution
{
public:
    bool verifyPostorder(vector<int> &postorder)
    {
        if (postorder.size() <= 1)
            return true;

        return recursive(postorder, 0, postorder.size() - 1);
    }

    bool recursive(vector<int> &postorder, int start, int end)
    {
        if (start >= end)
            return true; // 满足了所有搜索条件
        int firstRight = start;

        while (firstRight < end && postorder[firstRight] < postorder[end])
            ++firstRight;

        for (int i = firstRight; i < end; ++i)
        {
            if (postorder[i] < postorder[end])
                return false; // 不满足条件
        }

        return recursive(postorder, start, firstRight - 1) && recursive(postorder, firstRight, end - 1);
    }
};