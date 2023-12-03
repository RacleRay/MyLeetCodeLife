#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@File    :   单词阶梯.py
@Author  :   Racle
@Version :   1.0
@Desc    :   None
'''

"""
给一个起始单词和终止单词，问起始单词通过几次变换能够变成终止单词。
一次变换定义为改变单词一个字母，且变换过程中的单词需要在词典中出现。

"""

from collections import deque

CHARS = list('abcdefghijklmopqrstuvwxyz')

class Solution:
    def ladder_length(self, start, end, word_set):
        if start == end:
            return 0

        word_set.add(start)
        word_set.add(end)

        # 构建搜索图结构
        graph = self.construct_graph(word_set)

        f_queue = deque([start])
        f_set = set(f_queue)
        b_queue = deque([end])
        b_set = set(b_queue)

        distance = 0
        while f_queue and b_queue:
            distance += 1
            if self.extend_queue(graph, f_queue, f_set, b_set):
                return distance
            distance += 1
            if self.extend_queue(graph, b_queue, b_set, f_set):
                return distance

        return -1

    def extend_queue(self, graph, queue, visited, o_visited):
        for _ in range(len(queue)):
            word = queue.popleft()
            for nword in graph[word]:
                if nword in visited:
                    continue
                if nword in o_visited:
                    return True
                queue.append(nword)
                visited.add(nword)
        return False

    def construct_graph(self, word_set):
        graph = {}
        for word in word_set:
            graph[word] = self.get_next_words(word, word_set)
        return graph

    def get_next_words(self, word, word_set):
        next_word_set = set()
        for i in range(len(word)):
            prefix = word[: i]
            suffix = word[i + 1:]
            cur_char = word[i]
            for char in CHARS:
                if char == cur_char:
                    continue
                next_word = prefix + char + suffix
                if next_word in word_set:
                    next_word_set.add(next_word)
        return next_word_set


if __name__ == "__main__":
    solution = Solution()
