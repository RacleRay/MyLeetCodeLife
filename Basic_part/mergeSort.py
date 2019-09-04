# 自上而下的递归
def mergeSort(alist):

    if len(alist) <= 1:
        return alist

    # 分
    mid = len(alist) // 2
    left = alist[: mid]
    right = alist[mid: ]

    # 治之
    left = mergeSort(left)
    right = mergeSort(right)

    # 每一层递归收尾处理
    if left[-1] <= right[0]:
        alist = left + right
        return alist

    # merge smaller value
    p_l = p_r = p_k = 0
    while p_l < len(left) and p_r < len(right):
        if left[p_l] < right[p_r]:
            alist[p_k] = left[p_l]
            p_l += 1
        else:
            alist[p_k] = right[p_r]
            p_r += 1
        p_k += 1

    if p_l < len(left):
        alist += left[p_l: ]
    if p_r < len(right):
        alist += right[p_r: ]

    return alist


# 自底向上的归并排序
def merge(alist, left_bound, mid, right_bound):

    temp = alist[left_bound, right_bound + 1]

    # merge的两个窗口的init index
    left_i = left_bound
    right_i = mid + 1
    for i in range(left_bound, right_bound + 1):

        if left_i > mid:
            alist[i] = temp[right_i - left_bound]
            right_i += 1
        elif right_i > right_bound:
            alist[i] = temp[left_i - left_bound]
            left_i += 1

        elif temp[left_i - left_bound] < temp[right_i - right_bound]:
            alist[i] = temp[left_i - left_bound]  # 取小
            left_i += 1
        else:
            alist[i] = temp[right_i -left_bound]
            right_i += 1



def mergeSortBU(alist):

    n = len(alist)
    size = 1  # merge gap，merge窗口大小

    while size < n:
        for i in range(0, n - size, 2 * size):
            if alist[i + size - 1] > alist[i + size]:  # 检查是否有序
                # merge窗口的上下边界index
                left = i
                mid = i + size - 1
                right = min(i + 2 * size - 1, n - 1)
                # merge
                merge(alist, left, mid, right)
        size += size

    return alist