#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <unordered_map>

using namespace std;

// 输入一个非递减排序的数组的一个旋转，输出旋转数组的最小元素。
// 例如数组{3,4,5,1,2}为{1,2,3,4,5}的一个旋转，该数组的最小值为1。
// NOTE：给出的所有元素都大于0，若数组大小为0，请返回0。
class Solution
{
public:
    int minNumberInRotateArray(vector<int> &rotateArray)
    {
        if (rotateArray.size() == 0)
            return 0;
        for (int i = 0; i < rotateArray.size() - 1; i++)
        {
            if (rotateArray[i] > rotateArray[i + 1])
                return rotateArray[i + 1];
        }
        return rotateArray[0];
    }

    // 效率并没有提升
    int minNumberInRotateArray(vector<int> &rotateArray)
    {
        if (rotateArray.size() == 0)
            return 0;
        int left = 0, right = rotateArray.size() - 1;
        // 至少保证了两个值
        while (left + 1 < right)
        {
            int mid = left + (right - left) / 2;
            // 不是搜索 targe，这里需要留下边界值
            if (rotateArray[mid] < rotateArray[right])
                right = mid;
            // 相等的值，一个一个回退
            else if (rotateArray[mid] == rotateArray[right])
                right--;
            else
                left = mid;
        }
        return min(rotateArray[left], rotateArray[right]);
    }
};
