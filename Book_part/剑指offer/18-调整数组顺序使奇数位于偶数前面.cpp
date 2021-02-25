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
    vector<int> exchange(vector<int> &nums)
    {
        vector<int> temp(nums.size(), 0);
        int low = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            if ((nums[i] & 1) == 1)
                temp[low++] = nums[i];
        }
        for (int i = 0; i < nums.size(); i++)
        {
            if ((nums[i] & 1) == 0)
                temp[low++] = nums[i];
        }
        // nums.assign(temp.begin(), temp.end());
        return temp;
    }

    vector<int> exchange(vector<int> &nums)
    {
        int low = 0;
        int high = nums.size() - 1;
        while (low < high)
        {
            if ((nums[low] & 1) == 1)
                low++;
            else if ((nums[high] & 1) == 0)
                high--;
            else
                swap(nums[low++], nums[high--]);
        }
        return nums;
    }

    vector<int> exchange(vector<int> &nums)
    {
        int low = 0;  // 下一个奇数出现时，应该所在的位置
        int high = 0; // 最近还没有排序的奇数
        while (high < nums.size())
        {
            if ((nums[high] & 1) == 1)
                swap(nums[low++], nums[high]);
            high++;
        }
        return nums;
    }

    // slower
    vector<int> exchange(vector<int> &nums)
    {
        vector<int> temp(nums.size(), 0);
        int oddIndex = 0, evenIndex = 0;
        for (auto a : nums)
        {
            if ((a & 1) == 1)
                nums[oddIndex++] = a;
            else
                temp[evenIndex++] = a;
        }
        for (int i = 0; i < evenIndex; i++)
            nums[oddIndex + i] = temp[i];
        return nums;
    }
};