# python3

# 动态规划法
def getResult(str1, str2):
    len1 = len(str1)
    len2 = len(str2)
    result = ''
    common_len = 0
    common_end = 0

    # M[i][j]: 以str1[i], str2[j]结尾的最长公共子串的的长度
    M = [[None] * (len1 + 1) for _ in range(len2 + 1)]
    for i in range(len1 + 1):
        M[i][0] = 0
    for j in range(len2 + 1):
        M[0][j] = 0
    for i in range(1, len1 + 1):
        for j in range(1, len2 + 1):
            if str1[i - 1] == str2[j - 1]:  # M中多出第0行，第0列，对应str中idx要减一
                M[i][j] = M[i - 1][j - 1] + 1
                if M[i][j] > common_len:
                    common_len = M[i][j]
                    common_end = i
            else:
                M[i][j] = 0

    result = str1[common_end - common_len: common_end]
    return result


# 滑动比较
def getResult2(str1, str2):
    len1 = len(str1)
    len2 = len(str2)
    result = ''
    common_len = 0
    common_end = 0

    i = 0
    while i < len1 + len2:
        str1_begin = str2_begin = 0
        tmp_len = 0
        if i < len1:
            str1_begin =  len1 - i
        else:  # 补齐str2开始从右向左与str1相交的部分
            str2_begin =  i - len1
        # 遍历当前串与子串
        j = 0
        while (str1_begin + j < len1) and (str2_begin + j < len2):
            if str1[str1_begin + j] == str2[str2_begin + j]:
                tmp_len += 1
            else:
                if tmp_len > common_len:
                    common_len = tmp_len
                    common_end = str1_begin + j
                else:
                    tmp_len = 0
            j += 1
        i += 1

    result = str1[common_end - common_len: common_end]
    return result


if __name__ == "__main__":
    str1 = "abccade"
    str2 = "dgcadde"
    print(getResult(str1, str2))
    print(getResult2(str1, str2))