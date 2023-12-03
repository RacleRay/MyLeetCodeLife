#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@File    :   KnightShortestPath.py
@Author  :   Racle
@Version :   1.0
@Desc    :   None
'''

"""
在一个 n * m 的棋盘中(二维矩阵中 0 表示空 1 表示有障碍物)，骑士的初始位置是 (0, 0) ，
他想要达到 (n - 1, m - 1) 这个位置，骑士只能从 左边走到右边。
找出骑士到目标位置所需要走的最短路径并返回其长度，如果骑士无法达到则返回 -1.

"""

DIRECTOINS = [
    (-1, -2),
    (1, -2),
    (-2, -1),
    (2, -1)
]

class Solution:
    def shortestPath(self, grid):
        if not grid or not grid[0]:
            return -1

        n, m = len(grid), len(grid[0])

        dp = [[float('inf')] * 3 for _ in range(n)]

        dp[0][0] = 0

        for j in range(1, m):
            for i in range(n):
                if grid[i][j]:
                    continue
                for d_x, d_y in DIRECTOINS:
                    x, y = i + d_x, j + d_y
                    if 0 <= x < n and 0 <= y < m:
                        dp[i][j % 3] = min(dp[i][j % 3], dp[x][y % 3] + 1)

        if dp[n - 1][(m - 1) % 3] == float('inf'):
            return -1

        return dp[n - 1][(m - 1) % 3]


if __name__ == "__main__":
    solution = Solution()
    # grid = [[0,0,0,0],[0,0,0,0],[0,0,0,0]]
    grid = [[0,1,0],[0,0,1],[0,0,0]]
    print(solution.shortestPath(grid))
