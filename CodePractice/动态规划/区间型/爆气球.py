#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@File    :   爆气球.py
@Author  :   Racle
@Version :   1.0
@Desc    :   None
'''

"""
有一排气球，每个气球有一个分数。
戳爆一个球能获得其左右两边两个气球和这个气球的分数乘积。
找一个顺序，戳爆所有气球，使得获得的积分最大。

"""


class Solution:
    def boom(self, arr):
        # 方便搜索，设计两头一个 1
        if not arr:
            return 0

        nums = [1]
        nums.extend(arr)
        nums.append(1)

        n = len(nums)
        dp = [[0] * n for _ in range(n)]

        for length in range(3, n + 1): # 设计 nums 之后，长度至少为 3
            for i in range(n - length + 1):
                j = i + length - 1
                # 遍历 i 和 j 直接最后一个被戳爆的气球，计算dp状态
                for k in range(i + 1, j):
                    dp[i][j] = max(dp[i][j],
                        dp[i][k] + dp[k][j] + nums[i] * nums[k] * nums[j])

        return dp[0][n - 1]  # 最后一轮 nums[i] * nums[k] * nums[j] 为 1 * num * 1，不影响结果


if __name__ == "__main__":
    solution = Solution()
    print(solution.boom([3,1,5]))