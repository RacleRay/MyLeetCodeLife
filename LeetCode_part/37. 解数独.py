"""
编写一个程序，通过已填充的空格来解决数独问题。

一个数独的解法需遵循如下规则：

数字 1-9 在每一行只能出现一次。
数字 1-9 在每一列只能出现一次。
数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。
空白格用 '.' 表示。



一个数独。



答案被标成红色。

Note:

给定的数独序列只包含数字 1-9 和字符 '.' 。
你可以假设给定的数独只有唯一解。
给定数独永远是 9x9 形式的。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/sudoku-solver
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
"""
from collections import OrderedDict
from collections import defaultdict

class Solution(object):
    # def solveSudoku(self, board):
    #     """
    #     :type board: List[List[str]]
    #     :rtype: None Do not return anything, modify board in-place instead.
    #     """
    #     row = [[x for x in y if x != '.'] for y in board]
    #     col = [[x for x in y if x != '.'] for y in zip(*board)]
    #     pal = [[board[i+m][j+n] for m in range(3) for n in range(3) if board[i+m][j+n] != '.']\
    #          for i in (0, 3, 6) for j in (0, 3, 6)]
    #     # return all(len(set(x)) == len(x) for x in (*row, *col, *pal))

    #     self.dic = {}
    #     for i in range(9):
    #         for j in range(9):
    #             self.dic[(i, j)] = set(row[i] + col[j] + pal[(i // 3 ) * 3 + j // 3])

    #     self.dic = OrderedDict(sorted(self.dic.items(), key=lambda x: len(x[1]), reverse=True))

    #     if board == None or len(board) == 0:
    #         return None
    #     self.solve(board)

    # def solve(self, board):
    #     all_num = set(i for i in range(1, 10))
    #     for x in self.dic:
    #         row, col = x
    #         if board[row][col] != '.':
    #             continue
    #         else:
    #             for i in all_num - self.dic[x]:
    #                 if self.isValid(board, x, i):
    #                     board[row][col] = i
    #                     if self.solve(board): return True
    #                     else:
    #                         board[row][col] = '.'
    #             return False
    #     return True

    # def isValid(self, board, x, i):
    #     row, col = x
    #     for j in range(9):
    #         if board[j][col] != '.' and board[j][col] == i: return False
    #         if board[row][j] != '.' and board[row][j] == i: return False
    #         if board[(row // 3 ) * 3 + j // 3][(col // 3 ) * 3 + j % 3] != '.' \
    #                 and board[(row // 3 ) * 3 + j // 3][(col // 3 ) * 3 + j % 3] == i:
    #             return False
    #     return True

    def solveSudoku(self, board):
        """
        :type board: List[List[str]]
        :rtype: void Do not return anything, modify board in-place instead.
        """
        def could_place(d, row, col):
            """
            Check if one could place a number d in (row, col) cell
            """
            return not (d in rows[row] or d in columns[col] or \
                    d in boxes[box_index(row, col)])

        def place_number(d, row, col):
            """
            Place a number d in (row, col) cell
            """
            rows[row][d] += 1
            columns[col][d] += 1
            boxes[box_index(row, col)][d] += 1
            board[row][col] = str(d)

        def remove_number(d, row, col):
            """
            Remove a number which didn't lead
            to a solution
            """
            del rows[row][d]
            del columns[col][d]
            del boxes[box_index(row, col)][d]
            board[row][col] = '.'

        def place_next_numbers(row, col):
            """
            Call backtrack function in recursion
            to continue to place numbers
            till the moment we have a solution
            """
            # if we're in the last cell
            # that means we have the solution
            if col == N - 1 and row == N - 1:
                nonlocal sudoku_solved
                sudoku_solved = True
            #if not yet
            else:
                # if we're in the end of the row
                # go to the next row
                if col == N - 1:
                    backtrack(row + 1, 0)
                # go to the next column
                else:
                    backtrack(row, col + 1)


        def backtrack(row = 0, col = 0):
            """
            Backtracking
            """
            # if the cell is empty
            if board[row][col] == '.':
                # iterate over all numbers from 1 to 9
                for d in range(1, 10):
                    if could_place(d, row, col):
                        place_number(d, row, col)
                        place_next_numbers(row, col)
                        # if sudoku is solved, there is no need to backtrack
                        # since the single unique solution is promised
                        if not sudoku_solved:
                            remove_number(d, row, col)
            else:
                place_next_numbers(row, col)

        # box size
        n = 3
        # row size
        N = n * n
        # lambda function to compute box index
        box_index = lambda row, col: (row // n ) * n + col // n

        # init rows, columns and boxes
        rows = [defaultdict(int) for i in range(N)]
        columns = [defaultdict(int) for i in range(N)]
        boxes = [defaultdict(int) for i in range(N)]
        for i in range(N):
            for j in range(N):
                if board[i][j] != '.':
                    d = int(board[i][j])
                    place_number(d, i, j)

        sudoku_solved = False
        backtrack()


a=Solution()
b = a.solveSudoku([["5","3",".",".","7",".",".",".","."],["6",".",".","1","9","5",".",".","."],[".","9","8",".",".",".",".","6","."],["8",".",".",".","6",".",".",".","3"],["4",".",".","8",".","3",".",".","1"],["7",".",".",".","2",".",".",".","6"],[".","6",".",".",".",".","2","8","."],[".",".",".","4","1","9",".",".","5"],[".",".",".",".","8",".",".","7","9"]])
print(b)