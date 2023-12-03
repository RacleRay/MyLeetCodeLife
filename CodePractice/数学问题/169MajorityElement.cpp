#include "../header.h"


// Boyer-Moore Majority Vote
// 1. 要保证 Majority 一定存在，所以计算出结果后，需要进行再遍历验证
// 2. 这里的结果不需要验，题目写明了

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int majority = nums[0];
        int count = 1;

        for (int num: nums) {
            if (num == majority) {
                count++;
            } else {
                count--;
                if (count == 0) {
                    majority = num;
                    count = 1;
                }
            }
        }

        return majority;
    }
};