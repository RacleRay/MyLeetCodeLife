"""
n 皇后问题研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。



上图为 8 皇后问题的一种解法。

给定一个整数 n，返回 n 皇后不同的解决方案的数量。

示例:

输入: 4
输出: 2
解释: 4 皇后问题存在如下两个不同的解法。
[
 [".Q..",  // 解法 1
  "...Q",
  "Q...",
  "..Q."],

 ["..Q.",  // 解法 2
  "Q...",
  "...Q",
  ".Q.."]
]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/n-queens-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
"""
class Solution(object):
    def totalNQueens(self, n):
        """
        :type n: int
        :rtype: int
        """
        self.num = 0
        def DFS(queens, xy_dif, xy_sum):
            """深度优先

            Arguments:
                queens {int} -- 列
                xy_dif {int} -- 捺线
                xy_sum {int} -- 撇线
            """
            p = len(queens)
            if p == n:
                self.num += 1
                return
            for q in range(n):
                if q not in queens and p-q not in xy_dif and p+q not in xy_sum:
                    DFS(queens+[q], xy_dif+[p-q], xy_sum+[p+q])

        DFS([], [], [])  # 这里返回上一层就使用了上一层的参数xy，不需要remove全局变量
        return self.num

    def totalNQueens(self, n):
        """
        :type n: int
        :rtype: int
        """
        if n < 1: return None
        self.count = 0
        self.DFS(n, 0, 0, 0, 0)
        return self.count

    def DFS(self, n, row, cols, pie, na):
        # recursion terminator
        if row >= n:
            self.count += 1
            return

        # 得到当前所有的可用空位, 1表示可用，0为站位
        # ~(cols | pie | na)可用为位置
        # (1 << n) - 1：mask，只取最后n位为1
        bits = (~(cols | pie | na)) & ((1 << n) - 1)

        while bits:
            # -bits：取反在加1
            p = bits & -bits  # 取到可用位置最低位的1
            # 下一行p列不可用，pie线不可用，na线不可用
            # ‘<< 1’让站位的1下移，下一层迭代，~(cols | pie | na)变成站位信息
            self.DFS(n, row+1, cols | p, (pie | p) << 1, (na | p) >> 1)
            # 回溯将已经搜索过的1，删除
            bits = bits & (bits - 1)  # 去掉最低位的1