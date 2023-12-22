#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@File    :   栈实现队列.py
@Author  :   Racle
@Version :   1.0
@Desc    :   None
'''

"""

"""

class Solution:
    def __init__(self):
        self.stack1 = []
        self.stack2 = []

    def stack_move(self):
        if self.stack2:
            return
        while self.stack1:
            self.stack2.append(self.stack1.pop())

    def push(self, element):
        self.stack1.append(element)

    def top(self):
        self.stack_move()
        return self.stack2[-1]

    def pop(self):
        self.stack_move()
        return self.stack2.pop()


if __name__ == "__main__":
    solution = Solution()
