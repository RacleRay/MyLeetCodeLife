#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@File    :   全零子串.py
@Author  :   Racle
@Version :   1.0
@Desc    :   None
'''

"""
求出字符串中全0子串的个数

001000 有 5个0、3个00、1个000 共9个子串
"""


class Solution:
    def string_count(self, input_str):
        if not input_str:
            return 0

        j, answer = 1, 0
        for i in range(len(input_str)):
            if input_str[i] != '0':
                continue
            j = max(j, i + 1)
            while j < len(input_str) and input_str[j] == '0':
                j += 1
            answer += j - i

        return answer


if __name__ == "__main__":
    solution = Solution()
    print(solution.string_count("001000"))
