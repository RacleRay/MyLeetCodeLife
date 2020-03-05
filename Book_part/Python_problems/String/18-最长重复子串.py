"""banana -> ana"""


# 使用suffix后缀，可以从不同的idx开始获得子串。而prefix只会从相同的开头开始获得子串

def maxPrefixLen(str1, str2):
    i = 0
    while i < len(str1) and i < len(str2):
        if str1[i] == str2[i]:
            i += 1
        else:
            break
        i += 1
    return i


def getMaxCommonStr(string):
    length = len(string)
    suffixList = []
    i = 0
    while i < length:
        suffixList.append(string[i: ])
        i += 1
    suffixList.sort()

    commonStr = ''
    maxLen = 0
    i = 0
    while i < length - 1:
        tmpLen = maxPrefixLen(suffixList[i], suffixList[i + 1])
        if tmpLen > maxLen:
            maxLen = tmpLen
            commonStr = suffixList[i][: tmpLen]
        i += 1

    return commonStr


if __name__ == '__main__':
    string = "banana"
    print(getMaxCommonStr(string))