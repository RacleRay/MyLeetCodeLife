def divide(dividend, divisor):
    res = 0
    while dividend >= divisor:
        tmp = 1
        # 每次以2的指数量级增长divisor
        while tmp * divisor <= dividend >> 1:
            tmp <<= 1
        res += tmp
        dividend -= tmp * divisor
    return res


if __name__ == "__main__":
    print(divide(124, 4))