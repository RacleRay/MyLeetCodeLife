# 递归


def cal_power(base, power):
    if power == 0: return 1
    if power == 1: return base

    recursion = cal_power(base, abs(power) // 2)
    if power > 0:
        if power % 2 == 1:
            return recursion * recursion * base
        else:
            return recursion * recursion
    else:
        if power % 2 == 1:
            return 1 / (recursion * recursion * base)
        else:
            return 1 / (recursion * recursion)


if __name__ == "__main__":
    print(cal_power(2, 3))