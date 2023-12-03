#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@File    :   判断回文子串.py
@Author  :   Racle
@Version :   1.0
@Desc    :   None
'''

"""
区间型：

    题目会存在 Subarray/Substring 相关的字眼。
    用 dp[i][j] 表示数组/字符串中 i,j 这一段区间的最优值/可行性/方案总数。
    dp[i][j] = max/min/sum/or(dp[i,j 之内更小的若干区间])


问题：
O(n^2)的算法，检测任意一段字符串是不是回文串。

state: dp[i][j] 表示 i,j 这一段是不是回文串
function: dp[i][j] = dp[i + 1][j - 1] and s[i] == s[j]
initialization: dp[i][i] = true, dp[i][i + 1] == (s[i] == s[i + 1])
answer: dp[x][y] 对于任意想要检测是否是回文串的下标范围 x - y
"""

class Solution:
    def check(self, s, begin, end):
        if not s:
            return False
        if len(s) == 1:
            return True

        dp = [[False] * len(s) for _ in range(len(s))]
        for i in range(len(s) - 1):
            dp[i][i] = True
            dp[i][i + 1] = (s[i] == s[i + 1])
        dp[len(s) - 1][len(s) - 1] = True

        # 注意 dp 更新顺序，设计下标遍历顺序
        for length in range(3, len(s) + 1):
            for i in range(len(s) - length + 1):
                j = i + length - 1
                dp[i][j] = dp[i + 1][j - 1] and (s[i] == s[j])

        return dp[begin][end]


if __name__ == "__main__":
    solution = Solution()
    print(solution.check("abccba", 0, 4))
    print(solution.check("abccba", 0, 5))
    print(solution.check("abccba", 1, 4))