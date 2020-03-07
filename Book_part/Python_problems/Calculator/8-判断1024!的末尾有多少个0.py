"""因子分析：出现0的末尾，是因为出现了偶数与5相乘，与25相乘出现两个0，125相乘三个0，...
因此只要计算有多少个5因子。
"""

def zeroCount(n):
    """n/5, n/5^2, n/5^3, ..."""
    count = 0
    while n > 0:
        n //= 5
        count += n
    return count


if __name__ == "__main__":
    print(zeroCount(1024))