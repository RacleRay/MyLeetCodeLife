#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@File    :   unionFind.py
@Author  :   Racle
@Version :   1.0
@Desc    :   None
'''


class UnionFind:
    """可以证明，对于一个大小为 n 的集合，任何 m 次 union 或 find
    操作所需要的时间复杂度都是 O((m+n) α(n))，其中 α 是 Ackermann
    函数的反函数，一般可以视为常量
    """
    def __init__(self, n):
        self.up = list(range(n))
        self.rank = [0] * n

    def find(self, x):
        if self.up[x] == x:  # 父节点是自己
            return x
        else:
            self.up[x] = self.find(self.up[x])
            return self.up[x]

    def union(self, x, y):
        root_x = self.find(x)
        root_y = self.find(y)
        if root_x == root_y:
            return False
        if self.rank[root_x] == self.rank[root_y]:
            self.rank[root_x] += 1
            self.up[root_y] = root_x
        elif self.rank[root_x] > self.rank[root_y]:
            self.up[root_y] = root_x
        else:
            self.up[root_x] = root_y
        return True
