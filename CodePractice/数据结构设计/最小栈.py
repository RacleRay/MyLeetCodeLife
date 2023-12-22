#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@File    :   最小栈.py
@Author  :   Racle
@Version :   1.0
@Desc    :   None
'''

"""
设计一个栈，支持 O(1) push, pop, min
"""

class Solution:
    def __init__(self):
        self.stack = []
        self.min_stack = []

    def push(self, number):
        self.stack.append(number)
        # 只进不大于当前最小的元素
        if not self.min_stack or self.min_stack[-1] >= number:
            self.min_stack.append(number)

    def pop(self):
        number = self.stack.pop()
        if number == self.min_stack[-1]:
            self.min_stack.pop()
        return number

    def min(self):
        return self.min_stack[-1]


if __name__ == "__main__":
    solution = Solution()
