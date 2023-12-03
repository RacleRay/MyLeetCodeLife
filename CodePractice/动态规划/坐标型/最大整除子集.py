#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@File    :   最大整除子集.py
@Author  :   Racle
@Version :   1.0
@Desc    :   None
'''

"""
给一个由无重复的正整数组成的集合，找出一个元素最多的子集，
满足集合中任意两个元素 (Si, Sj) 都有 Si % Sj = 0 或 Sj % Si = 0
"""

class Solution:
    def largestDivisibleSubset(self, nums):
        if not nums:
            return []

        nums = sorted(nums)
        # n = len(nums)

        # dp[i] 表示以第 i 个数为结尾的最大整除子集个数
        # prev 记录 当前点与前一个点 之间的映射关系
        dp, prev = {}, {}
        for num in nums:
            dp[num] = 1
            prev[num] = -1

        last_num = nums[0]
        # 当 value 是个特别大的数，nums 数组比较小，应该遍历 index
        # 而不是 factors
        for num in nums:
            for factor in self.get_factors(num):
                if factor not in dp:
                    continue
                if dp[num] < dp[factor] + 1:
                    dp[num] = dp[factor] + 1
                    prev[num] = factor
            # 更新最大整除子集的最后一个数字
            if dp[num] > dp[last_num]:
                last_num = num

        return self.get_patch(prev, last_num)

    def get_patch(self, prev, last_num):
        path = []
        while last_num != -1:
            path.append(last_num)
            last_num = prev[last_num]
        return path[::-1]

    def get_factors(self, num):
        if num == 1:
            return []
        factor = 1
        factors = []
        while factor * factor <= num:
            if num % factor == 0:
                factors.append(factor)
                # 不可将 != 1 删掉，自己想想
                if factor * factor != num and factor != 1:
                    factors.append(num // factor)
            factor += 1
        return factors


if __name__ == "__main__":
    solution = Solution()
    nums = [1, 2, 4, 8]
    print(solution.largestDivisibleSubset(nums))

    nums_1 = [1, 2, 3]
    print(solution.largestDivisibleSubset(nums_1))