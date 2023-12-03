#include "../../header.h"


class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        vector<int> up(nums.size(), 0);
        vector<int> down(nums.size(), 0);
        up[1] = 1;
        down[1] = 1;

        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i - 1] >= nums[i]) {
                up[i] = up[i - 1];
            } else {
                up[i] = max(up[i - 1], down[i - 1] + 1);
            }

            if (nums[i - 1] <= nums[i]) {
                down[i] = down[i - 1];
            } else {
                down[i] = max(down[i - 1], up[i - 1] + 1);
            }
        }

        return max(up[nums.size() - 1], down[nums.size() - 1]);
    }
};