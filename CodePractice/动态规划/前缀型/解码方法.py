#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@File    :   解码方法.py
@Author  :   Racle
@Version :   1.0
@Desc    :   None
'''

"""
有一个消息包含A-Z通过以下规则编码
'A' -> 1
'B' -> 2
...
'Z' -> 26
现在给你一个加密过后的消息，问有几种解码的方式

输入: "12"
输出: 2
解释: 它可以被解码为 AB (1 2) 或 L (12).
"""

class Solution:
    def num_decoding(self, s):
        if not s:
            return 0

        n = len(s)

        # dp[i] 表示前 i 个字符有多少种解码方式
        dp = [0] * 3
        dp[0] = 1
        dp[1] = self.decode_check(s[0])

        for i in range(2, n + 1):
            dp[i % 3] = dp[(i - 1) % 3] * self.decode_check(s[i - 1: i]) + \
                    dp[(i - 1) % 3] * self.decode_check(s[i - 2: i])

        return dp[n % 3]

    def decode_ok(self, substr):
        code = int(substr)
        if len(substr) == 1 and code >= 1 and code <= 9:
            return 1
        if len(substr) == 2 and code >= 10 and code <= 26:
            return 1
        return 0


if __name__ == "__main__":
    solution = Solution()
