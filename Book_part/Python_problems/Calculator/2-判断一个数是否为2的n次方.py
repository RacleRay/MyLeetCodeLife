def isPowerOfTwo(n):
    if n < 1: return False
    i = 1
    while i <= n:
        if i == n: return True
        i <<= 1
    return False


def isPowerOfTwo2(n):
    if n < 1: return False
    return not (n & (n - 1))


if __name__ == "__main__":
    print(isPowerOfTwo(0))
    print(isPowerOfTwo2(4))