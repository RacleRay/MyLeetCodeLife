#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@File    :   通配符匹配.py
@Author  :   Racle
@Version :   1.0
@Desc    :   None
'''

"""
判断两个可能包含通配符“？”和“*”的字符串是否匹配。匹配规则如下：
- '?' 可以匹配任何单个字符。
- '*' 可以匹配任意字符串（包括空字符串）。
两个串完全匹配才算匹配成功。

1<=|s|, |p| <= 1000
s仅包含小写英文字母
p包含小写英文字母，?和*

求可行性
"""

class Solution:
    def is_match(self, source, pattern):
        if source == None or pattern == None:
            return False
        return self.is_match_helper(source, 0, pattern, 0)

    def all_star(self, pattern, p_index):
        for i in range(p_index, len(pattern)):
            if pattern[i] != '*':
                return False
        return True

    @staticmethod
    def is_match_char(s_char, p_char):
        return s_char == p_char or p_char == '?'

    def is_match_helper(self, source, s_index, pattern, p_index):
        # Out of time
        if p_index == len(pattern):
            return s_index == len(source)

        if s_index == len(source):
            return self.all_star(pattern, p_index)

        s_char = source[s_index]
        p_char = pattern[p_index]

        if p_char != '*':
            return self.is_match_char(s_char, p_char) and \
                self.is_match_helper(source, s_index + 1, pattern, p_index + 1)

        # p_char 为 *
        for i in range(s_index, len(source) + 1):
            if self.is_match_helper(source, i, pattern, p_index + 1):
                return True

        return False

    def is_match_helper2(self, source, s_index, pattern, p_index, memo):
        # 全匹配完
        if p_index == len(pattern):
            return s_index == len(source)

        if s_index == len(source):
            return self.all_star(pattern, p_index)

        # 记忆化剪枝
        if (s_index, p_index) in memo:
            return memo[(s_index, p_index)]

        s_char = source[s_index]
        p_char = pattern[p_index]
        match = False

        if p_char != '*':
            match = self.is_match_char(s_char, p_char) and \
                self.is_match_helper2(source, s_index + 1, pattern, p_index + 1, memo)
        # * 吃掉一个字符，或者 * 根本不匹配
        else:
            match = self.is_match_helper2(source, s_index, pattern, p_index + 1, memo) \
                or self.is_match_helper2(source, s_index + 1, pattern, p_index, memo)

        memo[(s_index, p_index)] = match

        return match


if __name__ == "__main__":
    solution = Solution()
    s = "ab"
    pat = "?*"
    print(solution.is_match(s, pat))

    s = "aa"
    pat = "a*"
    print(solution.is_match(s, pat))

    s = "aa"
    pat = "a"
    print(solution.is_match(s, pat))

