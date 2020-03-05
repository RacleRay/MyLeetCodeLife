def getMaxSub(string):
    """依次找到当前未遍历字符串中次序最大的char"""
    if string is None:
        return None
    length = len(string)
    result = [None for _ in range(length)]
    result[0] = string[-1]
    i = length - 2
    j = 0
    while i > 0:
        if string[i] >= result[j]:
            j += 1
            result[j] = string[i]
        i -= 1
    result = result[j: : -1]
    return ''.join(result)


if __name__ == '__main__':
    s = "acbdxmng"
    print(getMaxSub(s))