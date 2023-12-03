#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@File    :   k次替换后的最长重复字符.py
@Author  :   Racle
@Version :   1.0
@Desc    :   None
'''

"""
允许替换字符串中的字符 K 次，问替换之后，最长的重复字符有多长
"""

class Solution:
    def char_replacement(self, s, k):
        counter = {}
        answer = 0
        j = 0
        max_freq = 0
        for i in range(len(s)):
            # 越界退出，或者k不足以替换完少数字符
            while j < len(s) and j - i - max_freq <= k:
                counter[s[j]] = counter.get(s[j], 0) + 1
                max_freq = max(max_freq, counter[s[j]])
                j += 1
            # 当 k 不足以替换完当前的少数字符时
            if j - i - max_freq > k:
                # j - i 并删除上一个已完成检查的不合法字符
                answer = max(answer, j - i - 1)
            # 当 k 足够替换完少数字符
            else:
                answer = max(answer, j - i)

            # 滑动向后
            counter[s[i]] -= 1
            max_freq = max(counter.values())

        return answer



if __name__ == "__main__":
    solution = Solution()
    print(solution.char_replacement("ABABA", 2))
    print(solution.char_replacement("ABABC", 2))
    print(solution.char_replacement("ABCDCDE", 2))

