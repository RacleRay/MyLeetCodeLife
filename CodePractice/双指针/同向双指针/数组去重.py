#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@File    :   数组去重.py
@Author  :   Racle
@Version :   1.0
@Desc    :   None
'''

"""
去掉未排序数组中的重复元素

要求在 原数组上进行操作，也就是额外空间复杂度O(1)
"""

class Solution:
    def deduplication(self, nums):
        if not nums:
            return 0

        nums.sort()
        j = 1
        for i in range(len(nums)):
            while j < len(nums) and nums[j] == nums[i]:
                j += 1
            if j >= len(nums):
                break
            nums[i + 1] = nums[j]

        return nums, i + 1


if __name__ == "__main__":
    solution = Solution()
    ans, count = solution.deduplication([1,3,1,2,0,2])
    print(ans, count)
