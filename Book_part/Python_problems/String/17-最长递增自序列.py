# [Wrong !!!]Method1: 将目标串进行递增排序，之后求出两者最长公共子串
#   the neighbors might be changed after sort. "ghabcdoizu" -> "abcdghiouz". "o" didn't count.
def sortStr(string):
    strList = list(string)
    return ''.join(sorted(strList))

def getMaxAscending(string):
    sortedStr = sortStr(string)
    len1 = len(string)
    len2 = len(sortedStr)
    result = ''
    common_len = 0
    common_end = 0

    # M[i][j]: 以string[i], sortedStr[j]结尾的最长公共子串的的长度
    M = [[None] * (len1 + 1) for _ in range(len2 + 1)]
    for i in range(len1 + 1):
        M[i][0] = 0
    for j in range(len2 + 1):
        M[0][j] = 0
    for i in range(1, len1 + 1):
        for j in range(1, len2 + 1):
            if string[i - 1] == sortedStr[j - 1]:  # M中多出第0行，第0列，对应str中idx要减一
                M[i][j] = M[i - 1][j - 1] + 1
                if M[i][j] > common_len:
                    common_len = M[i][j]
                    common_end = i
            else:
                M[i][j] = 0

    result = string[common_end - common_len: common_end]
    return result

# Method2: 动态规划
def getDynamic(string):
    length = len(string)
    resultList = [0 for _ in range(length)]
    resultList[0] = 1  # 在idx为0处结束的最长递增子序列长度
    maxLen = 1

    i = 1
    while i < length:
        if string[i] > string[i - 1]:
            resultList[i] = resultList[i - 1] + 1
            if resultList[i] > maxLen:
                maxLen = resultList[i]
        else:
            resultList[i] = 1
        i += 1

    return maxLen


if __name__ == "__main__":
    s = "ghabcdoizu"
    # s = "xbcdza"
    # print(sortStr(s))
    print("Method 1 is WRONG: ", getMaxAscending(s))
    print("Method 2 is correct: ", getDynamic(s))