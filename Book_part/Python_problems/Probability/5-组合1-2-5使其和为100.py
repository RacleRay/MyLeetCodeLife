"""x + 2y + 5z = 100，转化为x + 5z <= 100，且x + 5z为偶数"""

def combineCount(n):
    count = 0
    x_limit = 0
    while x_limit <= n:
        nums_allowed = (x_limit + 2) // 2
        count += nums_allowed
        x_limit += 5
    return count


if __name__ == "__main__":
    print(combineCount(100))