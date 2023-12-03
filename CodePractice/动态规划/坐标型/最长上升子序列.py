#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@File    :   最长上升子序列.py
@Author  :   Racle
@Version :   1.0
@Desc    :   None
'''

"""
给定一个整数序列，找到最长上升子序列（LIS），返回LIS的长度。
"""

class Solution:
    def longestIncreasingSubsequence(self, nums):
        if nums is None or not nums:
            return 0

        dp = [1] * len(nums)
        prev = [-1] * len(nums)

        for i in range(len(nums)):
            for j in range(i):
                if nums[j] < nums[i] and dp[i] < dp[j] + 1:
                    dp[i] = dp[j] + 1
                    prev[i] = j

        longest, l_index = 0, -1
        for i in range(len(nums)):
            if dp[i] > longest:
                longest = dp[i]
                l_index = i

        path = []
        while l_index != -1:
            path.append(nums[l_index])
            l_index = prev[l_index]

        return path, longest


if __name__ == "__main__":
    solution = Solution()
    nums = [4,2,4,5,3,7]
    path, longest = solution.longestIncreasingSubsequence(nums)
    print(path[::-1])
    print(longest)
