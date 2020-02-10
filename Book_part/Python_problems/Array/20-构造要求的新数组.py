# python3


"""不适用除法，构造新数组为原数组中除了相应位置的数的所有数之积。"""


def newArray(arr):
    if len(arr) == 0:
        return
    res = [None for _ in range(len(arr))]
    LEN = len(arr)

    res[0] = 1
    i = 1
    while i < LEN:
        res[i] = res[i - 1] * arr[i - 1]  # 从左向右，不包括i
        i += 1

    res[0] = arr[LEN - 1]  # res[0]来记录从右向左之积
    i = LEN - 2
    while i >= 1:
        res[i] *= res[0]  # 从右向左，不包括i
        res[0] *= arr[i]
        i -= 1

    return res


if __name__ == '__main__':
    arr = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

    print("Result is:", newArray(arr))
