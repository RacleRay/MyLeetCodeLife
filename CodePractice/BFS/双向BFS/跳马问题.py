#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@File    :   跳马问题.py
@Author  :   Racle
@Version :   1.0
@Desc    :   None
'''

"""
[模板]
1. 初始化 forward_queue 和 forward_set ，加入起点
2. 初始化 backward_queue 和 backward_set ，加入起点
3. distance = 0
4. while forward_queue 和 backward_queue 都非空
5.     distance += 1
6.     for forward_queue
7.         扩展下一层的点放到 forward_queue 和 forward_set 中
8.         碰到 backward_set 中的点，return distance
9.     distance += 1
10.    for forward_queue
           扩展下一层的点放到 backward_queue 和 backward_set 中
           碰到 forward_set 中的点，return distance
11. return None
"""

"""
马从棋盘上的起点跳到终点需要最少花多少步？

grid 中 1 表示障碍
"""

from collections import deque


DIRECTIONS = (
    (1, 2),
    (-1, 2),
    (2, 1),
    (-2, 1),
    (-1, -2),
    (1, -2),
    (-2, -1),
    (2, -1)
)


class Solution:
    def shortest_path(self, grid, source, destination):
        if not grid or not grid[0]:
            return -1
        if grid[destination.x][destination.y]:
            return -1
        if (source.x, source.y) == (destination.x, destination.y):
            return 0

        f_queue = deque([(source.x, source.y)])
        f_set = set(f_queue)
        b_queue = deque([(destination.x, destination.y)])
        b_set = set(b_queue)

        distance = 0
        while f_queue and b_queue:
            distance += 1
            if self.extend_queue(grid, f_queue, f_set, b_set):
                return distance
            distance += 1
            if self.extend_queue(grid, b_queue, b_set, f_set):
                return distance

        return -1

    def extend_queue(self, grid, queue, visited, o_visited):
        for _ in range(len(queue)):
            x, y = queue.popleft()
            for dx, dy in DIRECTIONS:
                nx, ny = x + dx, y + dy
                if not self.is_valid(nx, ny, grid, visited):
                    continue
                if (nx, ny) in o_visited:
                    return True
                queue.append((nx, ny))
                visited.add((nx, ny))
        return False

    def is_valid(self, x, y, grid, visited):
        if x < 0 or x >= len(grid):
            return False
        if y < 0 or y >= len(grid[0]):
            return False
        if grid[x][y]:
            return False
        if (x, y) in visited:
            return False
        return True


if __name__ == "__main__":
    solution = Solution()
