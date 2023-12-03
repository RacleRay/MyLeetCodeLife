#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@File    :   石子归并游戏.py
@Author  :   Racle
@Version :   1.0
@Desc    :   None
'''

"""
石子排成一列，每次归并“相邻”的两堆石子。
每次归并的耗费是两堆石子之和，求最小总耗费。
"""


class Solution:
    def check(self, A):
        """
        state: dp[i][j] 表示下标 i 合并到 j 的最小耗费
        function: dp[i][j] = min(dp[i][k] + dp[k + 1][j]) + sum(i,j)
        initialization: dp[i][i] = 0
        answer: dp[0][n - 1]
        """
        n = len(A)

        if n < 2:
            return 0

        range_sum = self.range_sum_statistic(A, n)
        # 使用 prefix sum 来计算区间和的方法
        # prefix_sum = self.prefix_sum(A, n)

        dp = [[float('inf')] * n for _ in range(n)]
        for i in range(n):
            dp[i][i] = 0

        for length in range(2, n + 1):
            for i in range(n - length + 1):
                j = i + length - 1
                # 考虑如何划分一段为两堆
                # 其结果的差异来源于，被合并后的值再次被合并。
                # cur_cost = prefix_sum[j + 1] - prefix_sum[i]
                for mid in range(i, j):
                    dp[i][j] = min(dp[i][j],
                        dp[i][mid] + dp[mid + 1][j] + range_sum[i][j])
                    # dp[i][j] = min(dp[i][j],
                    #     dp[i][mid] + dp[mid + 1][j] + cost)

        return dp[0][n - 1]

    def range_sum_statistic(self, A, length):
        range_sum = [[0] * length for _ in range(length)]

        for i in range(length):
            range_sum[i][i] = A[i]

        for i in range(length):
            for j in range(i + 1, length):
                range_sum[i][j] = range_sum[i][j - 1] + A[j]

        return range_sum

    def prefix_sum(self, A, length):
        prefix_sum = [0] * (length + 1)
        for i in range(length):
            prefix_sum[i + 1] = prefix_sum[i] + A[i]
        return prefix_sum


if __name__ == "__main__":
    solution = Solution()
    print(solution.check([4,3,3,4]))