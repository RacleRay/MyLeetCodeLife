"""
有一个机器人的位于一个 m × n 个网格左上角。

机器人每一时刻只能向下或者向右移动一步。机器人试图达到网格的右下角。

现在考虑网格中有障碍物，那样将会有多少条不同的路径？
"""

class Solution:
    def unique_paths_with_obstacles(self, obstacle_grid):
        if not obstacle_grid or not obstacle_grid[0]:
            return 0

        rows, cols = len(obstacle_grid), len(obstacle_grid[0])
        dp = [[0] * cols for _ in range(rows)]

        for i in range(rows):
            if obstacle_grid[i][0]:
                break
            dp[i][0] = 1
        for j in range(cols):
            if obstacle_grid[0][j]:
                break
            dp[0][j] = 1

        for i in range(1, rows):
            for j in range(1, cols):
                if obstacle_grid[i][j]:
                    continue
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1]

        return dp[rows - 1][cols - 1]


if __name__ == "__main__":
    s = Solution()
    grid = [[0, 0, 1], [1, 0, 0], [0, 1, 0]]
    print(s.unique_paths_with_obstacles(grid))
