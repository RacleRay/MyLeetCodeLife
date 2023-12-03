"""
https://leetcode-cn.com/problems/word-ladder/


"""
import collections

# 超时，要使用双向bfs
class Solution:
    def ladderLength(self, beginWord: str, endWord: str, wordList: List[str]) -> int:
        if endWord not in wordList:
            return 0

        queue = collections.deque([beginWord])
        visited = set([beginWord])

        distance = 0
        while queue:
            distance += 1
            size = len(queue)
            for i in range(size):
                word = queue.popleft()
                if word == endWord:
                    return distance
                for next_word in self.get_next(word, wordList):
                    if next_word in visited:
                        continue
                    queue.append(next_word)
                    visited.add(next_word)

        return 0

    def get_next(self, word, wordList):
        next_words = []
        for nword in wordList:
            diff_flag = False
            for i in range(len(word)):
                if nword[i] != word[i]:
                    if diff_flag:
                        diff_flag = False # only one diff
                        break
                    diff_flag = True
            if diff_flag:
                next_words.append(nword)
        return next_words