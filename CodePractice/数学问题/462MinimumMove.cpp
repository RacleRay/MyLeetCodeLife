#include "../header.h"


class Solution {
public:
    int minMoves2(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        int median = nums[(nums.size() - 1) / 2];
        int res = 0;
        for (int num : nums) {
            res += abs(num - median);
        }

        return res;
    }
};