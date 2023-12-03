#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@File    :   两数只差.py
@Author  :   Racle
@Version :   1.0
@Desc    :   None
'''

"""
求两数之差等于给定的 target
(不适用额外空间 Two Sum 的第 11 个变形题)

NOTE:
当不能使用哈希表时，可以在排序数据集上进行二分来替代
不能使用哈希表的情况比如数据集很大，或者题目要求不适用额外空间
"""

class Solution:
    def two_sum_binary(self, nums, target):
        if not nums:
            return [-1, -1]

        target = abs(target)
        for i in range(len(nums)):
            j = self.binary_search(nums, i + 1, len(nums) - 1, target + nums[i])
            if j != -1:
                return [nums[i], nums[j]]
        return [-1, -1]

    def binary_search(self, nums, start, end, target):
        while start + 1 < end:
            mid = start + (end - start) // 2
            if nums[mid] < target:
                start = mid
            else:
                end = mid
        if nums[start] == target:
            return start
        if nums[end] == target:
            return end
        return -1

    # 同向双指针，i 右移差值变小，j 右移差值变大，逐步遍历到target的差值
    def two_sum_direction(self, nums, target):
        if not nums:
            return [-1, -1]

        target = abs(target)
        j = 1
        for i in range(len(nums)):
            j = max(j, i + 1) # j 若一直不更新，保证在 i 的前面
            while j < len(nums) and nums[j] - nums[i] < target:
                j += 1
            if j >= len(nums):
                break
            if nums[j] - nums[i] == target:
                return [nums[i], nums[j]]

        return [-1, -1]


if __name__ == "__main__":
    solution = Solution()
    nums = [0, 1, 3, 6, 14]
    print(solution.two_sum_binary(nums, 8))
    print(solution.two_sum_direction(nums, 8))
