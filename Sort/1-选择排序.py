def selectionSort(alist):
    if len(alist) == 0:
        return None

    lpoint = 0
    rpoint = len(alist) - 1
    while lpoint < rpoint:
        minIdx = lpoint
        maxIdx = rpoint
        if alist[minIdx] > alist[maxIdx]:
            alist[minIdx], alist[maxIdx] = alist[maxIdx], alist[minIdx]
        for i in range(lpoint + 1, rpoint):
            if alist[i] < alist[minIdx]:
                minIdx = i
            elif alist[i] > alist[maxIdx]:
                maxIdx = i
        alist[minIdx], alist[lpoint] = alist[lpoint], alist[minIdx]
        alist[maxIdx], alist[rpoint] = alist[rpoint], alist[maxIdx]
        lpoint += 1
        rpoint -= 1

    return alist


if __name__ == "__main__":
    l = [2, 3, 2, 4, 5, 5, 9, 8, 6]
    print(selectionSort(l))