#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@File    :   滑动窗口求和.py
@Author  :   Racle
@Version :   1.0
@Desc    :   None
'''

"""
求出数组中所有连续 k 个数之和

比如，nums = [1,2,7,8,5], k = 3，得到 [10,17,20]
"""

class Solution:
    def win_sum(self, nums, k):
        if not nums or len(nums) < k:
            return []

        result = []
        j, tmp_sum = 0, 0
        for i in range(len(nums)):
            while j < len(nums) and j - i < k:
                tmp_sum += nums[j]
                j += 1
            if j - i == k:
                result.append(tmp_sum)
            tmp_sum -= nums[i]

        return result


if __name__ == "__main__":
    solution = Solution()
    print(solution.win_sum([1,2,7,8,5], 3))