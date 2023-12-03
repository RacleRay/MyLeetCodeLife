#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@File    :   单词拆分2.py
@Author  :   Racle
@Version :   1.0
@Desc    :   None
'''

"""
给出一个单词表和一条去掉所有空格的句子，根据给出的单词表添加空格,
返回可以构成的句子的数量, 保证构成的句子中所有的单词都可以在单词表中找到.

求方案总数
"""

class Solution:
    def word_break(self, s, dict):
        if not s or not dict:
            return 0
        max_length, lower_dict = self.initialize(dict)
        return self.memo_search(s.lower(), 0, max_length, lower_dict, {})

    def initialize(self, dict):
        max_length, lower_dict = 0, set()
        for word in dict:
            max_length = max(max_length, len(word))
            lower_dict.add(word.lower())
        return max_length, lower_dict

    def memo_search(self, s, index, max_length, lower_dict, memo):
        if index == len(s):
            return 1
        if index in memo:
            return memo[index]
        result = 0
        for w_end in range(index + 1, len(s) + 1):
            if w_end - index > max_length:
                break
            word = s[index: w_end]
            if word not in lower_dict:
                continue
            result += self.memo_search(s, w_end, max_length, lower_dict, memo)
        memo[index] = result
        return memo[index]


if __name__ == "__main__":
    solution = Solution()
    s = "CatMat"
    dict = ["Cat", "Mat", "Ca", "tM", "at", "C", "Dog", "og", "Do"]
    print(solution.word_break(s, dict))
