def countSort(alist, maxElem):
    lens = len(alist)
    countList = [0] * (maxElem + 1)
    resList = [0] * lens

    for i in range(lens):
        countList[alist[i]] += 1

    # cumulate
    for i in range(1, len(countList)):
        countList[i] = countList[i] + countList[i - 1]

    for i in range(lens):
        # 由累计计数，转换为idx
        idx = countList[alist[i]] - 1
        resList[idx] = alist[i]
        countList[alist[i]] -= 1

    return resList

if __name__ == "__main__":
    l = [2, 3, 2, 4, 5, 5, 9, 8, 6]
    print(countSort(l, max(l)))