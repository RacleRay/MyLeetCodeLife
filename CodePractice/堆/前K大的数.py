"""
实现一个数据结构，提供下面两个接口 
1.add(number) 添加一个元素 
2.topk() 返回此数据结构中最大的k个数字。当我们创建数据结构时，k是给定的。
"""

import heapq

class Solution:
    def __init__(self, k):
        self.k = k
        self.heap = []

    def add(self, num):
        heapq.heappush(self.heap, num)
        if len(self.heap) > self.k:
            heapq.heappop(self.heap)

    def topk(self):
        return sorted(self.heap, reverse=True)