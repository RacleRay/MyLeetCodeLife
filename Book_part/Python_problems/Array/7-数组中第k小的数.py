# 快速排序思想，递归查找

def _find_small_k(arr, low, high, k):
    i = low
    j = high
    pivot = arr[i]

    while i < j:
        while i < j and arr[j] >= pivot:
            j -= 1

        if i < j:  # 可能是i == j
            arr[i] = arr[j]
            i += 1

        while i < j and arr[i] <= pivot:
            i += 1

        if i < j:
            arr[j] = arr[i]
            j -= 1

    arr[i] = pivot

    # arr[i]的位置
    position = i - low
    if position == k - 1:
        return arr[i]
    elif position > k - 1:
        return _find_small_k(arr, low, i - 1, k)
    else:
        return _find_small_k(arr, i + 1, high, k - position - 1)


def find_small_k(arr, k):
    if arr is None or len(arr) < k:
        return None

    return _find_small_k(arr, 0, len(arr) - 1, k)


if __name__ == "__main__":
    arr = [4, 0, 1, 0, 2, 3]
    print("result is: ", find_small_k(arr, 2))
