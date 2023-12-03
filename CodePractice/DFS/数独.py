#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@File    :   数独.py
@Author  :   Racle
@Version :   1.0
@Desc    :   None
'''

"""
9 x 9 数独

常规解法是使用数组或者哈希表记录每行、每列、每个3x3方格已使用的值

依照 index 依次遍历dfs
"""


class Solution:
    def solve(self, board):
        return self.dfs(board)

    def dfs(self, board):
        i, j, choices = self.get_least_choices_grid(board)

        if i is None:
            return True
        for val in choices:
            board[i][j] = val
            if self.dfs(board):
                return True
            board[i][j] = 0

        return False

    def is_valid(self, board, x, y, val):
        for i in range(9):
            if board[x][i] == val:
                return False
            if board[i][y] == val:
                return False
            # 九宫格内检查重复
            if board[x // 3 * 3 + i // 3][y // 3 * 3 + i % 3] == val:
                return False
        return True

    def get_least_choices_grid(self, board):
        # 选择当前棋盘中，选择更少的位置
        x, y, choices = None, None, [0] * 10
        for i in range(9):
            for j in range(9):
                if board[i][j] != 0:
                    continue
                # 当前 i，j 位置的分支可能性
                vals = []
                for val in range(1, 10):
                    if self.is_valid(board, i, j, val):
                        vals.append(val)
                if len(vals) < len(choices):
                    x, y, choices = i, j, choices
        return x, y, choices

if __name__ == "__main__":
    solution = Solution()
