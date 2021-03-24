#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <stack>
#include <set>
#include <unordered_map>
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
    int majorityElement(vector<int> &nums)
    {
        int maxcnt = 0, num = 0;
        for (int e : nums)
        {
            if (maxcnt == 0)
            {
                num = e;
                maxcnt = 1;
            }
            else
            {
                num == e ? maxcnt++ : maxcnt--;
            }
        }

        return maxcnt > 0 ? num : 0;
    }
};