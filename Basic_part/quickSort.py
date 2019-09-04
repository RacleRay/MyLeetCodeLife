
def quicksort(alist):
    """不是in-place的实现"""
    if len(alist) <= 1:
        return alist

    pivot = alist[len(alist) // 2]

    left = [x for x in alist if x < pivot]
    middle = [x for x in alist if x == pivot]
    right = [x for x in alist if x > pivot]

    return quicksort(left) + middle + quicksort(right)


# >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
# inplace
def partition(alist, left, right):
    """以pivot进行分组"""
    pivot = alist[right]
    # init left_index
    from_left_index = left

    for i in range(left, right):
        if alist[i] <= pivot:
            alist[from_left_index], alist[i] = alist[i], alist[from_left_index]
            from_left_index += 1

    # 交换：‘> pivot’的第一个元素 和 pivot元素
    alist[from_left_index], alist[right] = alist[right], alist[from_left_index]

    return from_left_index

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