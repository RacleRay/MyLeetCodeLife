"""
国际象棋的马，只能向右面的 4 个方向跳，求左上到右下最短路径
"""

DIRECTIONS = [
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

        # 从 0，0 到 i，j 的最少步数
        f = [[float('inf')] * m for _ in range(n)]

        f[0][0] = 0

        # 注意 i, j 遍历顺序，若先 i，那么只能向右条件下，会导致使用到未知结果的前一状态
        for j in range(m):
            for i in range(n):
                if grid[i][j]:
                    continue
                # 当前状态来自前一步可能四个状态
                for delta_x, delta_y in DIRECTIONS:
                    x, y = i + delta_x, j + delta_y
                    if 0 <= x < n and 0 <= y < m:
                        f[i][j] = min(f[i][j], f[x][y] + 1)

        if f[n - 1][m - 1] == float('inf'):
            return -1
        return f[n - 1][m - 1]