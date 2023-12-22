#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@File    :   队列实现栈.py
@Author  :   Racle
@Version :   1.0
@Desc    :   None
'''

"""

"""

from collections import deque


class Solution:
    def __init__(self):
        self.queue1 = deque()
        self.queue2 = deque()

    def push(self, x):
        self.queue1.append(x)

    def pop(self):
        # 保留队尾元素，弹出
        for _ in range(len(self.queue1) - 1):
            val = self.queue1.popleft()
            self.queue2.append(val)

        val = self.queue1.popleft()
        self.queue1, self.queue2 = self.queue2, self.queue1
        return val

    def top(self):
        val = self.pop()
        self.push(val)
        return val

    def is_empty(self):
        return not self.queue1

if __name__ == "__main__":
    solution = Solution()
