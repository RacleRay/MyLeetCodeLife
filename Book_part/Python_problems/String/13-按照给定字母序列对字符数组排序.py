def compare(string1, string2, charToInt):
    len1 = len(string1)
    len2 = len(string2)

    i = 0; j = 0
    while i < len1 and j < len2:
        if string1[i] not in charToInt:
            charToInt[string1[i]] = -1
        if string2[j] not in charToInt:
            charToInt[string2[j]] = -1
        if charToInt[string1[i]] < charToInt[string2[j]]:
            return -1
        elif charToInt[string1[i]] > charToInt[string2[j]]:
            return 1
        else:
            i += 1
            j += 1

    if i == len(string1) and j == len(string2):
        return 0
    elif i == len(string1):
        return -1
    else:
        return 1


def insertSort(stringList, charToInt):
    length = len(stringList)
    i = 1
    while i < length:
        tmp = stringList[i]
        j = i - 1
        while j >= 0:
            if compare(tmp, stringList[j], charToInt) == -1:  # tmp数值更小，优先级更高
                stringList[j + 1] = stringList[j]
            else:
                break
            j -= 1
        stringList[j + 1] = tmp
        i += 1
    return stringList


if __name__ == "__main__":
    li = ["bed", "dog", "dear", "eye"]
    order = "dgecfboa"
    charToInt = {}
    i = 0
    while i < len(order):
        charToInt[order[i]] = i
        i += 1
    print(insertSort(li, charToInt))
