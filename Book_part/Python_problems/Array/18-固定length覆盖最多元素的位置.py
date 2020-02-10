# python3


def maxCover(arr, L):
    max_cover = 1
    LEN = len(arr)
    start_idx = 0

    count = 2  # 起始有两个点
    start = 0
    end = 1
    while start < LEN and end < LEN:
        while end < LEN and (arr[end] - arr[start] <= L):
            end += 1
            count += 1
        # 跳出循环的情况，除掉
        end -= 1
        count -= 1
        if count > max_cover:
            max_cover = count
            start_idx = start
        start += 1
        end += 1

    return start_idx, max_cover


if __name__ == "__main__":
    arr = [1, 3, 7, 8, 10, 11, 12, 13, 15, 16, 17, 19, 25]
    start_idx, max_cover = maxCover(arr, 8)
    print("Result is: ", arr[start_idx: start_idx + max_cover])
