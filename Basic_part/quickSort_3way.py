from random import seed
from random import randint


seed(506)

def partition(alist, left, right):
    """3-way快排, 多重复值输入的情况，效果更好"""
    # 优化：防止近乎有序数组退化
    rand_i = randint(left, right)
    alist[right], alist[rand_i] = alist[rand_i], alist[right]
    pivot = alist[right]

    # init
    less_than_pivot = left - 1
    greater_than_pivot = right
    equal_pivot = left

    while equal_pivot < greater_than_pivot:

        if alist[equal_pivot] < pivot:
            alist[equal_pivot], alist[less_than_pivot + 1] = \
                alist[less_than_pivot + 1], alist[equal_pivot]
            equal_pivot += 1
            less_than_pivot += 1

        elif alist[equal_pivot] == pivot:
            equal_pivot += 1

        else:
            alist[equal_pivot], alist[greater_than_pivot - 1] = \
                alist[greater_than_pivot - 1], alist[equal_pivot]
            greater_than_pivot -= 1

    alist[right], alist[greater_than_pivot] = alist[greater_than_pivot], alist[right]

    return less_than_pivot, greater_than_pivot


def _quickSort(alist, left, right):
    if right > left:
        less_than_pivot, greater_than_pivot = partition(alist, left, right)
        _quickSort(alist, left, less_than_pivot)
        _quickSort(alist, greater_than_pivot + 1, right)


def quickSort(alist):

    if len(alist) <= 1:
        return alist

    _quickSort(alist, 0, len(alist)-1)

    return alist