"""详细算法介绍和性能对比见notebook"""

def gapInsertionSort(alist, startpos, gap):

    for i in range(startpos + gap, len(alist), gap):
        toBeInserted = alist[i]
        pointer = i

        # 间隔相同gap的位置，insertionSort
        while alist[pointer - gap] > toBeInserted and pointer >= gap:
            alist[pointer] = alist[pointer - gap]
            pointer = pointer - gap

        alist[pointer] = toBeInserted


def shellSort(alist):
    gap = 1
    # 生成最大gap
    while gap < len(alist) // 3:
        gap = gap * 3 + 1

    while gap > 0:
        for startpos in range(gap):
            gapInsertionSort(alist, startpos, gap)
        gap = gap // 3

    return alist