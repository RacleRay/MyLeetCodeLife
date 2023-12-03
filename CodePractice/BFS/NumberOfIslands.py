from collections import deque

DIRECTIONS = [(1, 0), (0, -1), (-1, 0), (0, 1)]

# https://www.lintcode.com/problem/433/description
# DFS will be more efficient

class Solution:
    def numIslands(self, grid):
        if not grid or not grid[0]:
            return 0

        self.n = len(grid)
        self.m = len(grid[0])
        islands = 0
        visited = set()

        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if grid[i][j] and (i, j) not in visited:
                    self.bfs(grid, i, j, visited)
                    islands += 1

        return islands

    def bfs(self, grid, x, y, visited):
        queue = deque([(x, y)])
        visited.add((x, y))
        while queue:
            x, y = queue.popleft()
            for dx, dy in DIRECTIONS:
                nextx = x + dx
                nexty = y + dy
                if not self.is_valid(grid, nextx, nexty, visited):
                    continue
                queue.append((nextx, nexty))
                visited.add((nextx, nexty))

    def is_valid(self, grid, x, y, visited):
        if not (0 <= x < self.n and 0 <= y < self.m):
            return False
        if (x, y) in visited:
            return False
        return grid[x][y]
