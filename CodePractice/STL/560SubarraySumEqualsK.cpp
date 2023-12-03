#include "../header.h"


// https://leetcode.cn/problems/subarray-sum-equals-k/submissions/

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int count = 0, psum = 0;
        unordered_map<int, int> hashmap;

        hashmap[0] = 1;   // psum , psum 对应的次数
        for (int num : nums) {
            psum += num;
            // psum - k 就是目标前缀和，psum - psum_prev 就是 k
            count += hashmap[psum - k];
            ++hashmap[psum];
        }

        return count;
    }
};