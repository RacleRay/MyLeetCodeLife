"""
给出一个由小写字母组成的矩阵和一个字典。
找出所有同时在字典和矩阵中出现的单词。
一个单词可以从矩阵中的任意位置开始，可以向左/右/ 上/下四个相邻方向移动。
一个字母在一个单词中只能被使用一次。且字典中不存在重复单词
"""

DIREECTIONS = [(0, 1), (0, -1), (1, 0), (1, 0)]


def wordSearch(board, words):
    if board is None or len(board) == 0:
        return []

    word_set = set(words)
    prefix_set = set()

    # get prefix
    for word in words:
        for i in range(len(word)):
            prefix_set.add(word[: i + 1])

    result_set = set()
    # dfs
    for i in range(len(board)):
        for j in range(len(board[0])):
            dfs(board, i, j, board[i][j], word_set, prefix_set, set([(i, j)]), result_set)

    return list(result_set)


def dfs(board, x, y, word, word_set, prefix_set, visited, result_set):
    if word not in prefix_set:
        return

    if word in word_set:
        result_set.add(word)

    for dx, dy in DIREECTIONS:
        nx = x + dx
        ny = y + dy
        if not legal(board, nx, ny) or (nx, ny) in visited:
            continue

        visited.add((nx, ny))
        dfs(board, nx, ny, word + board[nx][ny], word_set, prefix_set, visited, result_set)
        visited.remove((nx, ny))


def legal(board, x, y):
    return (0 <= x < len(board)) and (0 <= y < len(board[0]))
