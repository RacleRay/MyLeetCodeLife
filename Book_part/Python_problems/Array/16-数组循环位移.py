# python3


def reverse(arr, start, end):
    while start < end:
        arr[start], arr[end] = arr[end], arr[start]
        start += 1
        end -= 1


def rightShift(arr, k):
    """k -- 翻转截止index"""
    if arr is None:
        return

    length = len(arr)
    k %= length

    reverse(arr, 0, length - k - 1)
    reverse(arr, length - k, length - 1)
    reverse(arr, 0, length - 1)


if __name__ == "__main__":
    array = [1, 2, 3, 4, 5, 6, 7, 8, 9]
    rightShift(array, 5)

    print(array)