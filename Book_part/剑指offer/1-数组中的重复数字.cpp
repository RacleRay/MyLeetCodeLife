#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution
{
public:
    int findRepeatNumber(vector<int> &nums)
    {
        unordered_map<int, bool> map;
        for (int i : nums)
        {
            if (map[i] == true)
                return i;
            map[i] = true;
        }
        return -1;
    }
};

class Solution
{
public:
    // 假如元素排列好，那么，对应index的数字应当为index的数值
    int findRepeatNumber(vector<int> &nums)
    {
        int i = 0;
        while (i < nums.size())
        {
            if (nums[i] == i)
            {
                i++;
                continue;
            }
            // nums[i] 位置 已经是正确的值了，说明重复
            if (nums[i] == nums[nums[i]])
                return nums[i];
            // nums[i] 始终为 nums[i] 数值应当处于的 index 位置
            swap(nums[i], nums[nums[i]]);
        }
        return -1;
    }
};

int main(int argc, char *argv[])
{
    cout << "Passed" << endl;
}