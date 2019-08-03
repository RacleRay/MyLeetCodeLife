"""
n 皇后问题研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。



上图为 8 皇后问题的一种解法。

给定一个整数 n，返回所有不同的 n 皇后问题的解决方案。

每一种解法包含一个明确的 n 皇后问题的棋子放置方案，该方案中 'Q' 和 '.' 分别代表了皇后和空位。

示例:

输入: 4
输出: [
 [".Q..",  // 解法 1
  "...Q",
  "Q...",
  "..Q."],

 ["..Q.",  // 解法 2
  "Q...",
  "...Q",
  ".Q.."]
]
解释: 4 皇后问题存在两个不同的解法。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/n-queens
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
"""
class Solution(object):
    def solveNQueens(self, n):
        """
        :type n: int
        :rtype: List[List[str]]
        """
        if n < 1: return []
        self.result = []
        self.cols = set()
        self.pie = set()
        self.na = set()
        self.DFS(n, 0, [])
        return self._generate_result(n)

    def DFS(self, n, row, cur_state):
        # 深度优先
        if row >= n:
            self.result.append(cur_state)
            return

        # 遍历该层所有的列
        for col in range(n):
            # 不合法的格子
            if col in self.cols or row + col in self.pie or row - col in self.na:
                continue

            # 记录合法格子消去的格子
            self.cols.add(col)
            self.pie.add(row + col)  # 某一条斜线的和或者差是一定的
            self.na.add(row - col)

            # 此时该行已完成，下一行，直到第n层
            self.DFS(n, row + 1, cur_state + [col])

            # 一种解法成功后，继续下一种前，将每层逐步回退
            self.cols.remove(col)
            self.pie.remove(row + col)
            self.na.remove(row - col)

    def _generate_result(self, n):
        board = []
        for res in self.result:
            for i in res:  # res记录的是每一层的列
                board.append("." * i +"Q" + "." * (n - i - 1))
        return [board[i: i + n] for i in range(0, len(board), n)]


    def solveNQueens(self, n):
        """
        :type n: int
        :rtype: List[List[str]]
        """
        def DFS(queens, xy_dif, xy_sum):
            """深度优先

            Arguments:
                queens {int} -- 列
                xy_dif {int} -- 捺线
                xy_sum {int} -- 撇线
            """
            p = len(queens)
            if p == n:
                result.append(queens)
                return
            for q in range(n):
                if q not in queens and p-q not in xy_dif and p+q not in xy_sum:
                    DFS(queens+[q], xy_dif+[p-q], xy_sum+[p+q])

        result = []
        DFS([], [], [])  # 这里返回上一层就使用了上一层的参数xy，不需要remove全局变量
        return [ ["." * i +"Q" + "." * (n-i-1) for i in sol] for sol in result]