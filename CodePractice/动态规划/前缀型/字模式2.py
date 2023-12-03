#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@File    :   字模式2.py
@Author  :   Racle
@Version :   1.0
@Desc    :   None
'''

"""
给定一个pattern和一个字符串str，查找str是否遵循相同的模式。

这里遵循的意思是一个完整的匹配，在一个字母的模式和一个非空的单词str之间有一个双向连接的模式对应。
(如果a对应s，那么b不对应s。例如， 给定的模式= "ab"， str = "ss"，返回false）。
"""

class Solution:
    def word_pattern_match(self, pattern, string):
        return self.is_match(pattern, string, {}, set())

    def is_match(self, pattern, string, mapping, used):
        if not pattern:
            return not string

        char = pattern[0]
        if char in mapping:
            word = mapping[char]
            if not string.startswith(word):
                return False
            return self.is_match(pattern[1: ], string[len(word): ], mapping, used)

        for i in range(len(string)):
            word = string[: i + 1]

            if word in used:
                continue

            used.add(word)
            mapping[char] = word
            if self.is_match(pattern[1: ], string[i + 1: ], mapping, used):
                return True

            del mapping[char]
            used.remove(word)

        return False


if __name__ == "__main__":
    solution = Solution()
    pattern = "abab"
    s = "redblueredblue"
    print(solution.word_pattern_match(pattern, s))

    pattern = "aabb"
    s = "xyzabcxzyabc"
    print(solution.word_pattern_match(pattern, s))
