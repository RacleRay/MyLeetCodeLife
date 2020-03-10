def insertionSort(alist):
    lens = len(alist)
    for i in range(1, lens):
        toInsert = alist[i]
        insertIdx = i
        while alist[insertIdx - 1] > toInsert and insertIdx > 0:
            alist[insertIdx] = alist[insertIdx - 1]
            insertIdx -= 1
        alist[insertIdx] = toInsert
    return alist


if __name__ == "__main__":
    l = [2, 3, 2, 4, 5, 5, 9, 8, 6]
    print(insertionSort(l))
