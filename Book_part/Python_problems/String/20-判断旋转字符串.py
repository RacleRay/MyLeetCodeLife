"""假设字符串收尾相连，组成圆环，是否存在不同起终点的两个字符串是相同的"""


def isSubStr(str1, str2):
    """KMP算法"""
    if str1 is None or str2 is None:
        return False

    slen = len(str1)
    plen = len(str2)
    if slen < plen:
        return False

    def getNextKMP(pattern):
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

    nexts_list = getNextKMP(str2)

    i = 0
    j = 0
    while i < slen and j < plen:
        if j == -1 or str1[i] == str2[j]:
            i += 1
            j += 1
        else:
            # 回溯到pattern中记录的前缀重复位置，再与str1匹配
            j = nexts_list[j]

    if j == plen:
        return True

    return False


def isRotateSub(str1, str2):
    if str1 is None or str2 is None:
        return False

    len1 = len(str1)
    len2 = len(str2)
    if len1 != len2:
        return False

    res = isSubStr(str1 + str1, str2)
    return res


if __name__ == "__main__":
    str1 = "waterbottle"
    str2 = "erbottlewat"
    print(isRotateSub(str1, str2))