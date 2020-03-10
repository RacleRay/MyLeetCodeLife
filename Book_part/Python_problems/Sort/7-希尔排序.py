def gapInsertionSort(alist, start, gap):
    for i in range(start + gap, len(alist), gap):
        toInsert = alist[i]
        insertIdx = i
        while alist[insertIdx - gap] > toInsert and insertIdx >= gap:
            alist[insertIdx] = alist[insertIdx - gap]
            insertIdx -= gap
        alist[insertIdx] = toInsert


def shellSort(alist):
    gap = 1
    while gap < len(alist) // 3:
        gap = gap * 3 + 1

    while gap > 0:
        for start in range(gap):
            gapInsertionSort(alist, start, gap)
        gap //= 3  # # gap will be：1, 4, 13, 40, 121, 364, 1093...

    return alist


if __name__ == "__main__":
    l = [2, 3, 2, 4, 5, 5, 9, 8, 6]
    print(shellSort(l))