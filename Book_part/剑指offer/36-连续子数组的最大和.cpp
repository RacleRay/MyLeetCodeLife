#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <stack>
#include <set>
#include <unordered_map>
#include <queue>
#include <functional>
#include <cmath>
#include <bitset>
#include <stdio.h>
#include <string.h>
#include <limits.h>

using namespace std;


class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if (nums.size()==0) return 0;

        int maxsum = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            nums[i] = max(0, nums[i-1]) + nums[i];
            maxsum = max(maxsum, nums[i]);
        }
        return maxsum;
    }


    int maxSubArray(vector<int>& nums) {
        if (nums.size()==0) return 0;

        int maxsum = nums[0];

        vector<int> dp(nums.size(), 0);
        dp[0] = nums[0];

        for (int i = 1; i < nums.size(); i++){
            dp[i] = max(nums[i], dp[i - 1] + nums[i]);
            maxsum = max(maxsum, dp[i]);
        }

        return maxsum;
    }
};