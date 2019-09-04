from random import randint
from random import seed


seed(506)

def partition(alist, left, right):
    """双路快速排序的partition，优化有多重复元素的数组的退化"""
    # 优化：防止近乎有序数组退化
    rand_i = randint(left, right)
    alist[right], alist[rand_i] = alist[rand_i], alist[right]
    pivot = alist[right]

    # init
    left_index = left
    right_index = right - 1

    while True:
        # 符合顺序条件的情况
        while left_index <= right - 1 and alist[left_index] < pivot:
            left_index += 1
        while right_index >= left and alist[right_index] > pivot:
            right_index -= 1

        if left_index > right_index:
            break

        alist[left_index], alist[right_index] = alist[right_index], alist[left_index]
        left_index += 1
        right_index -= 1

    alist[right], alist[left_index] = alist[left_index], alist[right]

    return left_index


def _quickSort(alist, left, right):
    if right > left:
        p_index = partition(alist, left, right)
        _quickSort(alist, left, p_index - 1)
        _quickSort(alist, p_index + 1, right)


def quickSort(alist):

    if len(alist) <= 1:
        return alist

    _quickSort(alist, 0, len(alist)-1)

    return alist