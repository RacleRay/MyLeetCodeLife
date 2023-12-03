#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@File    :   单词拆分3.py
@Author  :   Racle
@Version :   1.0
@Desc    :   None
'''

"""
给一字串s和单词的字典dict, 在字串中增加空格来构建一个句子，并且所有单词都来自字典。
返回所有有可能的句子。

不适合动规
"""

class Solution:
    def word_break(self, s, dict):
        if not s or not dict:
            return []
        max_length = len(max(dict, key=len))
        result = []
        self.dfs(s, 0, max_length, dict, {}, [], result)
        return result

    def dfs(self, s, index, max_length, word_set, memo, path, result):
        if index == len(s):
            result.append(" ".join(path))
            return

        # 剪枝
        if not self.is_possible(s, index, max_length, word_set, memo):
            return

        for w_end in range(index + 1, len(s) + 1):
            if w_end - index > max_length:
                break
            word = s[index: w_end]
            if word not in word_set:
                continue
            path.append(word)
            self.dfs(s, w_end, max_length, word_set, memo, path, result)
            path.pop()

        return

    def is_possible(self, s, index, max_length, dict, memo):
        # 搜索 index 之后，是否可行，这里可以使用记忆化搜索
        if index in memo:
            return memo[index]
        if index == len(s):
            return True
        for w_end in range(index + 1, len(s) + 1):
            if (w_end - index) > max_length:
                break
            word = s[index: w_end]
            if word not in dict:
                continue
            if self.is_possible(s, w_end, max_length, dict, memo):
                memo[index] = True
                return True  # 这里需要记录True，因为dfs中找所有解，就可能重复遍历
        memo[index] = False
        return False

    # ===========================================================
    def word_break2(self, s, word_dict):
        # 另一种解法：直接记忆的是从 i 开始，后缀的划分方案。
        if not s or not word_dict:
            return []

        max_length = len(max(word_dict, key=len))
        return self.dfs2(s, max_length, word_dict, {})

    def dfs2(self, s, max_length, word_dict, memo):
        if s in memo:
            return memo[s]
        if len(s) == 0:  # 这一判断似乎没必要
            return []

        partitions = []
        for prefix_len in range(1, len(s)):
            if prefix_len > max_length:
                break
            prefix = s[: prefix_len]
            if prefix not in word_dict:
                continue
            sub_partitions = self.dfs2(s[prefix_len: ], max_length, word_dict, memo)
            # 情况一，即使 prefix 遍历到了，但是 sub_partitions 为空，那么不会将 prefix 加入到结果集
            for partition in sub_partitions:
                partitions.append(prefix + " " + partition)

        # 关键一步，当情况一发生，这一步将 dict 中的词，加入partitions中
        if s in word_dict:
            partitions.append(s)

        memo[s] = partitions
        return partitions


if __name__ == "__main__":
    solution = Solution()
    s = "lintcode"
    dict = ["de","ding","co","code","lint"]
    print(solution.word_break(s, dict))
    print(solution.word_break2(s, dict))

    s = "a"
    dict = []
    print(solution.word_break(s, dict))
    print(solution.word_break2(s, dict))