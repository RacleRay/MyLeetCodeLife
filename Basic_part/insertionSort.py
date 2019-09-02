def insertionSort(alist):

    for i in range(1, len(alist)):
        toBeInserted = alist[i]
        pointer = i

        # 大的值后移
        while alist[pointer-1] > toBeInserted and pointer > 0:
            alist[pointer] = alist[pointer - 1]
            pointer -= 1

        # 插入正确位置
        alist[pointer] = toBeInserted

    return alist