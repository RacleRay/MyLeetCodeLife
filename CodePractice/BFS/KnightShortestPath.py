# https://www.lintcode.com/problem/611/



DIRECTIONS = [(-2, -1), (-2, 1), (-1, 2), (1, 2), (2, 1), (2, -1), (1, -2), (-1, -2)]


class Solution:
    def shortest_path(self, grid, source, dest):
        queue = collections.deque([(source.x, source.y)])

        distance_dict = {(source.x, source.y): 0}

        while queue:
            x, y = queue.popleft()
            if (x, y) == (dest.x, dest.y):
                return distance_dict[(x, y)]
            for dx, dy in DIRECTIONS:
                nextx, nexty = x + dx, y + dy
                if not self.isvalid(nextx, nexty, grid):
                    continue
                if (nextx, nexty) in distance_dict:
                    continue
                queue.append((nextx, nexty))
                distance_dict[(nextx, nexty)] = distance_dict[(x, y)] + 1

        return -1

    def isvalid(self, x, y, grid):
        n, m = len(grid), len(grid[0])
        if x < 0 or x >= n or y < 0 or y >= m:
            return False
        return not grid[x][y]
