#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@File    :   编辑距离.py
@Author  :   Racle
@Version :   1.0
@Desc    :   None
'''

"""
将一个字符串通过“增删改”字符变成另外一个字符串.
问最少编辑次数是多少

dp[i][j] 表示第一个字符串的前 i 个字符通过最少多少次编辑可以变成第二个字符串的前 j 个字
"""

class Solution:
    def min_dist(self, word1, word2):
        if not word1 or not word2:
            return -1

        n, m = len(word1), len(word2)

        dp = [[0] * (m + 1) for _ in range(n + 1)]

        for i in range(n + 1):
            dp[i][0] = i
        for j in range(m + 1):
            dp[0][j] = j

        for i in range(1, n + 1):
            for j in range(1, m + 1):
                # word1 删除一个字符，余下进行匹配
                # word1 增加一个字符，j字符将新字符匹配了，余下进行匹配
                dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + 1
                if word1[i - 1] == word2[j - 1]:
                    dp[i][j] = min(dp[i][j], dp[i - 1][j - 1])
                else:
                    dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + 1)

        return dp[n][m]

    def min_dist2(self, word1, word2):
        if not word1 or not word2:
            return -1

        n, m = len(word1), len(word2)

        dp = [[0] * (m + 1) for _ in range(2)]

        # for i in range(2):
        #     dp[i][0] = i
        for j in range(m + 1):
            dp[0][j] = j

        for i in range(1, n + 1):
            dp[i % 2][0] = i
            for j in range(1, m + 1):
                # word1 删除一个字符，余下进行匹配
                # word1 增加一个字符，j字符将新字符匹配了，余下进行匹配
                dp[i % 2][j] = min(dp[(i - 1) % 2][j], dp[i % 2][j - 1]) + 1
                if word1[i - 1] == word2[j - 1]:
                    dp[i % 2][j] = min(dp[i % 2][j], dp[(i - 1) % 2][j - 1])
                else:
                    dp[i % 2][j] = min(dp[i % 2][j], dp[(i - 1) % 2][j - 1] + 1)

        return dp[n % 2][m]


if __name__ == "__main__":
    solution = Solution()
    print(solution.min_dist("horse", "rose"))
    print(solution.min_dist2("horse", "rose"))

    print(solution.min_dist("abc", "abd"))
    print(solution.min_dist2("abc", "abd"))

    print(solution.min_dist("intention", "execution"))
    print(solution.min_dist2("intention", "execution"))