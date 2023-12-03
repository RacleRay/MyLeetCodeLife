#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@File    :   数字三角形.py
@Author  :   Racle
@Version :   1.0
@Desc    :   None
'''

"""
给定一个数字三角形，找到从顶部到底部的最小路径和。
每一步可以移动到下面一行的相邻数字上。
"""

class Solution:
    def minimum(self, triangle):
        if not triangle or not triangle[0]:
            return -1

        n = len(triangle)

        dp = [[0] * n, [0] * n]
        dp[0][0] = triangle[0][0]

        for i in range(1, n):
            dp[i % 2][0] = dp[(i - 1) % 2][0] + triangle[i][0]
            dp[i % 2][i] = dp[(i - 1) % 2][i - 1] + triangle[i][i]
            for j in range(1, i):
                dp[i % 2][j] = min(dp[(i - 1) % 2][j], dp[(i - 1) % 2][j - 1]) + triangle[i][j]

        return min(dp[(n - 1) % 2])


if __name__ == "__main__":
    solution = Solution()
    triangle = [ [2], [3, 4], [6, 5, 7], [4, 1, 8, 3] ]
    print(solution.minimum(triangle))
