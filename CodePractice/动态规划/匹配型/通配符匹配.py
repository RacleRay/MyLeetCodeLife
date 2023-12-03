#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@File    :   通配符匹配.py
@Author  :   Racle
@Version :   1.0
@Desc    :   None
'''

"""
isMatch(aab, c*a*b) = false
isMatch(abc, *?c) = true

'?' 可以匹配任何单个字符。
'*' 可以匹配任意字符串（包括空字符串）

dp[i][j] = source的前i个字符能否匹配上pattern的前j个字符
"""

class Solution:
    def is_match(self, source, pattern):
        if source is None or pattern is None:
            return False

        n, m = len(source), len(pattern)

        dp = [[False] * (m + 1) for _ in range(n + 1)]

        dp[0][0] = True
        for i in range(1, m + 1):
            dp[0][i] = dp[0][i - 1] and pattern[i - 1] == '*'

        for i in range(1, n + 1):
            for j in range(1, m + 1):
                if pattern[j - 1] == '*':
                    # * 匹配0个，或者 * 号匹配1个及以上
                    dp[i][j] = dp[i - 1][j] or dp[i][j - 1]
                else:
                    dp[i][j] = dp[i - 1][j - 1] and (
                        source[i - 1] == pattern[j - 1] or pattern[j - 1] == '?'
                    )

        return dp[n][m]

    def is_match2(self, source, pattern):
        if source is None or pattern is None:
            return False

        n, m = len(source), len(pattern)

        dp = [[False] * (m + 1) for _ in range(2)]

        dp[0][0] = True
        for i in range(1, m + 1):
            dp[0][i] = dp[0][i - 1] and pattern[i - 1] == '*'

        for i in range(1, n + 1):
            dp[i % 2][0] = False  # 除了0,0是True，其他应该初始化为False
            for j in range(1, m + 1):
                if pattern[j - 1] == '*':
                    # * 匹配0个，或者 * 号匹配1个及以上
                    dp[i % 2][j] = dp[(i - 1) % 2][j] or dp[i % 2][j - 1]
                else:
                    dp[i % 2][j] = dp[(i - 1) % 2][j - 1] and (
                        source[i - 1] == pattern[j - 1] or pattern[j - 1] == '?'
                    )

        return dp[n % 2][m]


if __name__ == "__main__":
    solution = Solution()
    print(solution.is_match("aab", "c*a*b"))
    print(solution.is_match("abc", "*?c"))

    print(solution.is_match2("aab", "c*a*b"))
    print(solution.is_match2("abc", "*?c"))
