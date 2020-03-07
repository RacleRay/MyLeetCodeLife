# Method1: 向右移位
def countOne(n):
    count = 0
    while n > 0:
        if (n & 1) == 1:  # 当前最后一位是否为1
            count += 1
        n >>= 1
    return count


# Method2: 与操作删除当前最靠右的1，执行操作为当前二进制中1的个数
def countOne2(n):
    count = 0
    while n > 0:
        n = n & (n - 1)
        count += 1
    return count


if __name__ == "__main__":
    print(countOne(7))
    print(countOne2(7))
