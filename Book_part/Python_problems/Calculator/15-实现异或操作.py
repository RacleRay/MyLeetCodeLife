def xor(a, b):
    BITS = 32
    result = 0

    i = BITS - 1
    while i >= 0:
        cur_bit_a = (a & (1 << i)) > 0
        cur_bit_b = (b & (1 << i)) > 0
        cur_bit_xor = 0 if cur_bit_a == cur_bit_b else 1
        result <<= 1
        result |= cur_bit_xor
        i -= 1
    return result


def xor2(a, b):
    return (a | b) & (~(a & b))


if __name__ == "__main__":
    print(xor(3, 5))
    print(xor2(3, 5))
