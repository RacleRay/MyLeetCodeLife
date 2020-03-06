def binary_search(n):
    low = 1
    high = n
    while low <= high:
        mid = (low + high) // 2
        square = mid ** 2
        if square > n:
            high = mid - 1
        elif square < n:
            low = mid + 1
        else:
            return True
    return False


def arithmetic_sequence(n):
    seq = 1
    while n > 0:
        n = n - seq
        if n > 0:
            seq += 2
        elif n < 0:
            return False
        else:
            return True


if __name__ == "__main__":
    # !python -m cProfile 1-判断一个自然数是否是某个数的平方.py
    n = 12319230129
    print(binary_search(n), arithmetic_sequence(n))