def maxSubArray(arr):
    """暴力求解
    """
    if arr is None:
        return

    cur_sum = 0
    max_sum = 0

    i = 0
    while i < len(arr):
        j = i
        while j < len(arr):  # 遍历片段
            cur_sum = 0
            k = i
            while k <= j:  # 计算可能片段的和
                cur_sum += arr[k]
                k += 1
            if cur_sum > max_sum:
                max_sum = cur_sum
            j += 1
        i += 1

    return max_sum


def maxSubArray2(arr):
    """利用已计算的值
    """
    if arr is None:
        return

    max_sum = 0

    i = 0
    while i < len(arr):
        cur_sum = 0
        j = i
        while j < len(arr):
            cur_sum += arr[j]
            if cur_sum > max_sum:
                max_sum = cur_sum
            j += 1
        i += 1

    return max_sum


def maxSubArray3(arr):
    """动态规划
    """
    if arr is None:
        return

    length = len(arr)
    EndWithLast = [None] * length
    All = [None] * length

    EndWithLast[-1] = arr[-1]  # 包含结尾元素的情况的最大值列表
    All[-1] = arr[-1]

    EndWithLast[0] = arr[0]
    All[0] = arr[0]

    i = 1
    while i < length:
        EndWithLast[i] = max(EndWithLast[i-1] + arr[i], arr[i])  # 连续子数组
        All[i] = max(EndWithLast[i], All[i-1])  # 考虑不包含结尾元素
        i += 1

    return All[-1]


def maxSubArray4(arr):
    """优化空间复杂度
    """
    if arr is None:
        return

    length = len(arr)
    iEndWithLast = arr[0]
    iAll = arr[0]

    i = 1
    while i < length:
        iEndWithLast = max(iEndWithLast + arr[i], arr[i])
        iAll = max(iEndWithLast, iAll)
        i += 1

    return iAll


if __name__ == "__main__":
    array = [1, -2, 4, 8, -4, 7, -1, 10]
    print("Result is: ", maxSubArray4(array))
