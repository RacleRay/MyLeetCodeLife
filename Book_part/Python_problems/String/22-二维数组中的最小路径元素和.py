import functools


def memorize(func):
    """缓存已计算结果，也可以考虑lru cache wrapper"""
    memo = {}
    @functools.wraps(func)
    def funcAfterMemo(*args):
        if (args[1], args[2]) not in memo:
            memo[(args[1], args[2])] = func(*args)
        return memo[(args[1], args[2])]
    return funcAfterMemo


@memorize
def getMinPath(matrix, i, j):
    """递归路径"""
    if i == 0 and j == 0:
        return matrix[i][j]
    elif i > 0 and j > 0:
        return matrix[i][j] + min(getMinPath(matrix, i - 1, j),
                                  getMinPath(matrix, i, j - 1))
    elif i > 0 and j == 0:
        return matrix[i][j] + getMinPath(matrix, i - 1, j)
    else:
        return matrix[i][j] + getMinPath(matrix, i, j - 1)


def getMinPathUser(matrix):
    if matrix is None:
        return None
    return getMinPath(matrix, len(matrix) - 1, len(matrix[0]) - 1)


if __name__ == "__main__":
    matrix = [[1, 4, 3], [8, 7, 5], [2, 1, 5]]
    print(getMinPathUser(matrix))