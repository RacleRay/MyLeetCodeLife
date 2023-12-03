/*
给定一个数组 nums，编写一个函数将所有 0
移动到数组的末尾，同时保持非零元素的相对顺序。

示例:

输入: [0,1,0,3,12]
输出: [1,3,12,0,0]
说明:

必须在原数组上操作，不能拷贝额外的数组。
尽量减少操作次数。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/move-zeroes
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

*/

// 最少操作次数，所以一般遇到非 0 就交换的做法肯定是错的。
// 思路先填充，后补0


#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        if (nums.size() <= 1) return;

        vector<int>::iterator pad_p  = nums.begin();
        vector<int>::iterator scan_p = nums.begin();

        while (scan_p != nums.end()) {
            if (*scan_p != 0) {
                if (pad_p != scan_p) *pad_p = *scan_p;  // 不管pad_p现在是不是0
                ++pad_p;  // 实际上等于是非0的最后一个位置
            }
            ++scan_p;
        }

        // ++pad_p;
        while (pad_p != nums.end()) {
            if (*pad_p != 0) *pad_p = 0;
            ++pad_p;
        }

        return;
    }
};