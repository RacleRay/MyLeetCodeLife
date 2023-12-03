#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@File    :   01背包.py
@Author  :   Racle
@Version :   1.0
@Desc    :   None
'''

"""
n个物品(A), m大小的背包，问最多能装多满

注意：此问题没有方向性，即 A 中物品大小是可以无序进行遍历转移状态的
"""

class Solution:
    def backPack(self, m, A):
        n = len(A)

        # dp[i][j] : 前i个数中是否存在能组成j的若干个数
        dp = [[False] * (m + 1) for _ in range(n + 1)]

        dp[0][0] = True
        for i in range(1, n + 1):
            dp[i][0] = True
            for j in range(1, m + 1):
                if j >= A[i - 1]:  # index begins from 0
                    dp[i][j] = dp[i - 1][j] or dp[i - 1][j - A[i - 1]]
                else:
                    dp[i][j] = dp[i - 1][j]

        for i in range(m, -1, -1):
            if dp[n][i]:
                return i

        return -1

    def backPack2(self, m, A):
        n = len(A)

        # dp[i][j] : 前i个数中所能组成的 <= j 的最大和
        dp = [[0] * (m + 1) for _ in range(n + 1)]

        # 效率比前一方法慢一点，因为 + 比 or 慢
        for i in range(1, n + 1):
            for j in range(0, m + 1):
                if j >= A[i - 1]:
                    dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - A[i - 1]] + A[i - 1])
                else:
                    dp[i][j] = dp[i - 1][j]

        return dp[n][m]


if __name__ == "__main__":
    solution = Solution()
