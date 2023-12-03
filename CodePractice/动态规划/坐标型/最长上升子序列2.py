#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@File    :   最长上升子序列2.py
@Author  :   Racle
@Version :   1.0
@Desc    :   None
'''

"""
给定一个整数矩阵. 找出矩阵中的最长连续上升子序列, 返回它的长度.
最长连续上升子序列可以从任意位置开始, 向上/下/左/右移动.
"""

class Solution:
    def longestIncreasingSubsequence(self, A):
        if not A or not A[0]:
            return

        n, m = len(A), len(A[0])

        points = []
        for i in range(n):
            for j in range(m):
                points.append((A[i][j], i, j))

        points.sort()

        longest_hash = {}
        for i in range(len(points)):
            key = (points[i][1], points[i][2])
            longest_hash[key] = 1
            for dx, dy in [(1, 0), (0, -1), (-1, 0), (0, 1)]:
                x, y = points[i][1] + dx, points[i][2] + dy
                if x < 0 or x >= n or y < 0 or y >= m:
                    continue
                # if (x, y) in longest_hash and A[x][y] < points[i][0]:
                # 由于排过序，A中值升序遍历。所以，A[x][y] < points[i][0] 时，
                # A[x][y]必定遍历过
                if A[x][y] < points[i][0]:
                    longest_hash[key] = max(longest_hash[key],
                                            longest_hash[(x, y)] + 1)

        return max(longest_hash.values())



if __name__ == "__main__":
    solution = Solution()
    A = [
        [1,2,3,4,5],
        [16,17,24,23,6],
        [15,18,25,22,7],
        [14,19,20,21,8],
        [13,12,11,10,9]
    ]
    print(solution.longestIncreasingSubsequence(A))
