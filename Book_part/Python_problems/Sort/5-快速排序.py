import random

def partition(alist, start, end):
    randPivot = random.randint(start, end)
    alist[end], alist[randPivot] = alist[randPivot], alist[end]
    pivot = alist[end]

    lpoint = start
    rpoint = end - 1
    while True:
        while lpoint < end and alist[lpoint] < pivot:
            lpoint += 1
        while rpoint > start and alist[rpoint] > pivot:
            rpoint -= 1
        if lpoint > rpoint:
            break
        alist[lpoint], alist[rpoint] = alist[rpoint], alist[lpoint]
        lpoint += 1
        rpoint -= 1
    # lpoint在退出循环时，alist[lpoint] >= pivot。交换后，大于pivot的值还是在右侧
    alist[end], alist[lpoint] = alist[lpoint], alist[end]
    return lpoint


def quicksort(alist, start, end):
    if start > end:
        return None
    pivotIdx = partition(alist, start, end)
    quicksort(alist, start, pivotIdx - 1)
    quicksort(alist, pivotIdx + 1, end)


def quickSort(alist):
    if len(alist) <= 1:
        return alist
    quicksort(alist, 0, len(alist) - 1)
    return alist


if __name__ == "__main__":
    l = [2, 3, 2, 4, 5, 5, 9, 8, 6]
    print(quickSort(l))
