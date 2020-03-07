def add(num1, num2):
    sums = num1 ^ num2
    carry = num1 & num2
    while carry != 0:
        num1 = sums
        num2 = carry << 1
        sums = num1 ^ num2
        carry = num1 & num2
    return sums


def multi(a, b):
    sign_neg = (a > 0) ^ (b > 0)  # 符号
    if a < 0:
        a = add(~a, 1)
    if b < 0:
        b = add(~b, 1)

    result = 0
    bit_position = {1 << i: i for i in range(32)}
    while b > 0:
        position = bit_position[b & ~(b - 1)]  # 最右边的1
        result += a << position
        b &= (b - 1)  # 去掉最右边的1

    if sign_neg:
        result = add(~result, 1)

    return result


if __name__ == "__main__":
    print(multi(230, -3))