#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@File    :   最大栈.py
@Author  :   Racle
@Version :   1.0
@Desc    :   None
'''

"""
实现 push, pop, top, peekMax, popMax
"""

import heapq


class Solution:
    def __init__(self):
        self.heap = []
        self.stack = []
        self.popped_set = set()
        self.count = 0

    def push(self, x):
        item = (-x, -self.count)
        self.stack.append(item)
        heapq.heappush(self.heap, item)
        self.count += 1

    def pop(self):
        # 检查是否在popMax之后，被标记删除的元素，在stack中还没有被删除，并将其删除
        self._clear_popped_in_stack()
        # 删除stack元素，并标记在heap中遇到时，需要处理，即加入 popped_set
        item = self.stack.pop()
        self.popped_set.add(item)
        return -item[0]

    def top(self):
        self._clear_popped_in_stack()
        item = self.stack[-1]
        return -item[0]

    def peek_max(self):
        self._clear_popped_in_heap()
        item = self.heap[0]
        return -item[0]

    def pop_max(self):
        self._clear_popped_in_heap()
        item = heapq.heappop(self.heap)
        self.popped_set.add(item)
        return -item[0]

    def _clear_popped_in_stack(self):
        while self.stack and self.stack[-1] in self.popped_set:
            self.popped_set.remove(self.stack[-1])
            self.stack.pop()

    def _clear_popped_in_heap(self):
        while self.heap and self.heap[0] in self.popped_set:
            self.popped_set.remove(self.heap[0])
            heapq.heappop(self.heap)


if __name__ == "__main__":
    solution = Solution()
