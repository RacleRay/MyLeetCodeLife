"""详细算法介绍和性能对比见notebook"""

def selectionSort(alist):
    """同时查找最大最小"""
    left = 0
    right = len(alist) - 1

    while left < right:
        minIndex = left
        maxIndex = right

        if alist[minIndex] > alist[maxIndex]:
            alist[minIndex], alist[maxIndex] = alist[maxIndex], alist[minIndex]

        for i in range(left + 1, right):
            if alist[i] < alist[minIndex]:
                minIndex = i
            elif alist[i] > alist[maxIndex]:
                maxIndex = i

        # left is min, right is max. Next loop
        alist[left], alist[minIndex] = alist[minIndex], alist[left]
        alist[right], alist[maxIndex] = alist[maxIndex], alist[right]

        left += 1
        right -= 1

    return alist