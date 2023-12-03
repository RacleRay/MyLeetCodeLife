
#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@File    :   单词拆分.py
@Author  :   Racle
@Version :   1.0
@Desc    :   None
'''

"""
给定字符串 s 和单词字典 dict，确定 s 是否可以分成一个或多个以空格分隔的子串，
并且这些子串都在字典中存在。

求可行性
"""

class Solution:
    # stack overflow
    def wordBreak(self, s, dict):
        if not s:
            return True
        if not dict:
            return False
        max_length = len(max(dict, key=len))
        return self.dfs(s, 0, max_length, dict, {})

    def dfs(self, s, index, max_length, dict, memo):
        # 从 index 开始的字符串，能否划分成功
        if index in memo:
            return memo[index]

        if index == len(s):
            return True

        for word_end in range(index + 1, len(s) + 1):
            if (word_end - index) > max_length:
                break
            word = s[index: word_end]
            if word not in dict: # find a word
                continue
            # 可行解，找到直接返回
            if self.dfs(s, word_end, max_length, dict, memo):
                return True
        # 正确会直接返回，错误才可能遇到重复遍历
        memo[index] = False
        return False

    def word_break_dp(self, s, wordset):
        if not s:
            return True

        n = len(s)
        dp = [False] * (n + 1)
        dp[0] = True

        max_len = max([len(word) for word in wordset])

        for i in range(1, n + 1):
            for l in range(1, max_len + 1):
                if i < l:
                    break
                if not dp[i - l]:
                    continue
                word = s[i - l: i]
                if word in wordset:
                    dp[i] = True
                    break

        return dp[n]


if __name__ == "__main__":
    solution = Solution()
    s = "lintcode"
    dict = ["de","ding","co","code","lint"]
    print(solution.wordBreak(s, dict))
    print(solution.word_break_dp(s, dict))