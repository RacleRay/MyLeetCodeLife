#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;


/**
 * @brief 
 在一个长度为n的数组里的所有数字都在0到n-1的范围内。 数组中某些数字是重复的，但不知道有几个数字是重复的。
 也不知道每个数字重复几次。请找出数组中第一个重复的数字。 
 
 例如，如果输入长度为7的数组{2,3,1,0,2,5,3}，那么对应的输出是第一个重复的数字2。
 * 
 */


class Solution
{
public:
    int findRepeatNumber(vector<int> &nums)
    {
        unordered_map<int, bool> map;
        map.reserve(nums.size());
        for (int i : nums)
        {
            if (map[i] == true)
                return i;
            map[i] = true;
        }
        return -1;
    }
};

class Solution2
{
public:
    // 
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

    int findRepeatNumber2(vector<int> &nums) {
        int length = nums.size();
        for (int i = 0; i < length; i++) {
            int index = nums[i] % length;
            if (nums[index] >= length) {
                return index;
            }
            nums[index] += length;
        }

        return -1;
    }
};


int main(int argc, char *argv[])
{
    cout << "Passed" << endl;
}