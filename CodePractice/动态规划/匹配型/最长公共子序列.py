#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@File    :   最长公共子序列.py
@Author  :   Racle
@Version :   1.0
@Desc    :   None
'''

"""
ABCD 和 ACBD 的 LCS 是 ACD 或者 ABD

dp[i][j] 表示第一个字符串的前i个字符与第二个字符串的前j个字符的 LCS 多长
"""

class Solution:
    def longest_common_subsequence(self, A, B):
        if not A or not B:
            return 0

        n, m = len(A), len(B)
        dp = [[0] * (m + 1) for i in range(n + 1)]

        for i in range(1, n + 1):
            for j in range(1, m + 1):
                # s1[i - 1] != s2[j - 1]
                dp[i][j] = max(dp[i][j - 1], dp[i - 1][j])
                if A[i - i] == B[j - 1]:
                    # s1[i - 1] == s2[j - 1]
                    # "cabc" "accc" , 其中 第3个c可以不匹配
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1)


if __name__ == "__main__":
    solution = Solution()
