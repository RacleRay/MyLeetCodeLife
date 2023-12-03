#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@File    :   分块检索算法.py
@Author  :   Racle
@Version :   1.0
@Desc    :   None
'''

"""
将长度为 N 的区间分成 √N 的大小的小区间
总共 √N 个小区间，每个小区间统计局部的数据
因此在这些区间中进行增删查改的效率是 O(√N)

统计每个数前面比他小的数
[1, 2, 7, 8, 5] 每个数前面比他小的数分别为 [0, 1, 2, 3, 2]
"""


import random


class Block:
    def __init__(self):
        self.total = 0
        self.counter = {}


class BlockArray:
    def __init__(self, max_value, bins=100):
        self.bins = bins
        self.blocks = [
            Block() for _ in range(max_value // bins + 1)
        ]

    def count_smaller(self, value):
        count = 0
        # smaller blocks
        block_index = value // self.bins
        for i in range(block_index):
            count += self.blocks[i].total
        # smaller values in block
        counter = self.blocks[block_index].counter
        for val in counter:
            if val < value:
                count += counter[val]
        return count

    def insert(self, value):
        block_index = value // self.bins
        block = self.blocks[block_index]
        block.total += 1
        block.counter[value] = block.counter.get(value, 0) + 1


class Solution:
    def count_smaller_number(self, A):
        if not A:
            return []

        block_array = BlockArray(10000, 100)
        results = []
        for a in A:
            count = block_array.count_smaller(a)
            results.append(count)
            block_array.insert(a)

        return results


if __name__ == "__main__":
    solution = Solution()
    A = []
    for i in range(100000):
        A.append(random.randint(0, 10000))
    print(solution.count_smaller_number(A))
