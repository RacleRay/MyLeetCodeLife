"""判断str1是否为str2的子串"""


# Method1: 直接求解
def match(source, pattern):
    if source is None or pattern is None:
        return None

    slen = len(source)
    plen = len(pattern)
    if slen < plen:
        return None

    i = 0
    j = 0
    while i < slen and j < plen:
        if source[i] == pattern[j]:
            i += 1
            j += 1
        else:
            i = i - j + 1  # j相当于i偏移的长度
            j = 0
            if i > slen - plen:  # 没有足够的长度匹配pattern
                return None
    if j == plen:  # pattern匹配完全
        return i - plen

    return None


# Method2: KMP
def getNextKMP(pattern):
    """找到pattern中，从开头开始到某一位置处，是否在pattern后面部分是否重复，并记录这一位置
    nexts_list的第一位，相当于回溯运算的起点。
    """
    nexts_list = [None for _ in range(len(pattern) + 1)]

    i = 0
    j = -1
    nexts_list[i] = j
    while i < len(pattern):
        if j == -1 or pattern[i] == pattern[j]:
            i += 1
            j += 1
            nexts_list[i] = j
        else:
            j = nexts_list[j]

    return nexts_list

def matchKMP(source, pattern, nexts_list):
    if source is None or pattern is None:
        return None

    slen = len(source)
    plen = len(pattern)
    if slen < plen:
        return None

    i = 0
    j = 0
    while i < slen and j < plen:
        if j == -1 or source[i] == pattern[j]:
            i += 1
            j += 1
        else:
            # 回溯到pattern中记录的前缀重复位置，再与source匹配
            j = nexts_list[j]

    if j == plen:
        return i - plen

    return None


if __name__ == "__main__":
    s = "asfnasf"
    p = "nas"
    print(match(s, p))

    nexts_list = getNextKMP(p)
    print(matchKMP(s, p, nexts_list))



