#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@File    :   全子集问题.py
@Author  :   Racle
@Version :   1.0
@Desc    :   None
'''

"""
求一个集合的所有子集

子集中的元素不能以降序排列，解集不能包含重复的子集。
"""

class Solution:
    def subsets(self, nums):
        if not nums:
            return [[]]

        queue = [[]]
        index = 0
        while index < len(queue):
            subset = queue[index]
            index += 1
            for num in nums:
                if subset and subset[-1] >= num:
                    continue
                queue.append(subset + [num])

        return queue

    def subsets2(self, nums):
        if not nums:
            return [[]]

        queue = [[]]
        for num in sorted(nums):
            for i in range(len(queue)):
                subset = list(queue[i])
                subset.append(num)
                queue.append(subset)

        return queue


if __name__ == "__main__":
    solution = Solution()
    nums = [1, 2, 3]
    print(solution.subsets(nums))
    print(solution.subsets2(nums))
