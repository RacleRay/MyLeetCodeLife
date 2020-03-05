def getMaxDupChar(string, start, curMaxLen, maxLen):
    if start == len(string) - 1:
        return max(curMaxLen, maxLen)
    if string[start] == string[start + 1]:
        curMaxLen += 1
        return getMaxDupChar(string, start + 1, curMaxLen, maxLen)
    else:
        maxLen = max(curMaxLen, maxLen)
        curMaxLen = 1
        return getMaxDupChar(string, start + 1, curMaxLen, maxLen)


if __name__ == "__main__":
    print(getMaxDupChar("sfasgaffasfefg", 0, 1, 1))