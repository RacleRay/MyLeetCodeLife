def longToBinary(n):
    longBits = 64
    bits = []
    # 常规十进制转二进制算法
    mod = n % 2
    bits.append(str(mod))
    for i in range(longBits - 1):
        n >>= 1
        mod = n % 2
        bits.append(str(mod))
    return ''.join(bits[::-1])


def longToHex(n):
    # 和转二进制算法相同的思路
    hexBits = 16
    hexs = ""
    reminder = 0
    while hexBits != 0:
        remainder = n % 16
        if remainder < 10:
            hexs = str(remainder) + hexs
        else:
            hexs = chr(remainder - 10 + ord('A')) + hexs
        n >>= 4
        hexBits -= 1
    return hexs


if __name__ == "__main__":
    print(longToBinary(10))
    print(longToHex(10))