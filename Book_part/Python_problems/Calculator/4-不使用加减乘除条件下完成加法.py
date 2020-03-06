def add(num1, num2):
    """加法的一种计算方式，分解为 sums -- 每个位置相加但不考虑进位的结果；
    carry -- 每个位置来自低位的进位
    """
    sums = 0
    carry = 0
    while True:
        sums = num1 ^ num2
        carry = (num1 & num2) << 1
        num1 = sums
        num2 = carry
        if carry == 0:
            return sums


if __name__ == "__main__":
    print(add(123, 321))