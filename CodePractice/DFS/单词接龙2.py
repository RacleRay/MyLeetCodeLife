"""
给出两个单词（start和end）和一个字典，找出所有从start到end的最短转换序列。
变换规则如下：
    每次只能改变一个字母。
    变换过程中的中间单词必须在字典中出现
"""

# BFS：处理如何找打最短
# DFS: 处理如何找到路径

import string
from collections import deque

def findLadder(start, end, d):
    d.add(start)
    d.add(end)

    # BFS
    distances = {}
    from_to_dic = {}
    for word in d:
        from_to_dic[word] = []

    bfs(start, distances, from_to_dic, d)

    results = []
    dfs(start, end, distances, d, [], results, from_to_dic, distances[end])

    return results

def bfs(start, distance_dic, from_to_dic, d):
    distance_dic[start] = 0
    queue = deque([start])
    while queue:
        curr_word = queue.popleft()
        for next_word in get_next_word(curr_word, d):
            # new word or next_word和目前最短的已遍历路径中的相同词在同一层，curr_word 可以转到 next_word
            if (next_word not in distance_dic) or (distance_dic[next_word] == distance_dic[curr_word] + 1):
                from_to_dic[curr_word].append(next_word)
            # update distance records
            if next_word not in distance_dic:
                distance_dic[next_word] = distance_dic[curr_word] + 1
                queue.append(next_word)

def get_next_word(word, d):
    words = []
    for i in range(len(word)):
        for c in string.ascii_lowercase:
            if word[i] == c:
                continue
            next_word = word[:i] + c + word[i + 1: ]
            if next_word in d:
                words.append(next_word)
    return words

def dfs(curr_word, target, distance, d, path, results, from_to_dic, min_len):
    # min_len 来自distance_dic中end词的位置，BFS中已经遍历得到了最短的target所在的位置
    if len(path) == min_len + 1:
        return

    path.append(curr_word)

    if curr_word == target:
        results.append(list(path))
    else:
        for next_word in from_to_dic[curr_word]:
            dfs(next_word, target, distance, d, path, results, from_to_dic, min_len)

    path.pop()
