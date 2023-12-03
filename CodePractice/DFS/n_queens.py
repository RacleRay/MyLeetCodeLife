#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@File    :   n_queens.py
@Author  :   Racle
@Version :   1.0
@Desc    :   None
'''

"""
N皇后问题是将n个皇后放置在n*n的棋盘上，
皇后彼此之间不能相互攻击(任意两个皇后不能位于同一行，同一列，同一斜线)。
"""

"""
另一个版本优化思路：
    使用哈希表，记录哪些列、哪些斜线已经被用过。
    使得 is_valid 不用再使用 O(N) 的时间复杂度。
    但是并不能影响 O(N^2) 的 draw 函数对整体时间复杂度的影响
"""

class Solution:
    def solve(self, n):
        results = []
        self.search(n, [], results)
        return results

    def search(self, n, cols, results):
        row = len(cols) # cols 长度区分每一行
        if row == n:
            results.append(self.draw_chessboard(cols))
            return
        for col in range(n):
            if not self.is_valid(cols, row, col):
                continue
            cols.append(col)
            self.search(n, cols, results)
            cols.pop()

    def draw_chessboard(self, cols):
        "cols : 存的是每一行中，哪一列是queen"
        n = len(cols)
        board = []
        for i in range(n):
            row = ['Q' if j == cols[i] else '.' for j in range(n)]
            board.append(''.join(row))
        return board

    def is_valid(self, cols, row, col):
        for r, c in enumerate(cols):
            if c == col:  # col 列是否已被使用
                return False
            # r - c 正斜率斜线， r + c 负斜率斜线
            if r - c == row - col or r + c == row + col:
                return False
        return True


if __name__ == "__main__":
    solution = Solution()
