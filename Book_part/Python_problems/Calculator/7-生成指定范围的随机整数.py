import random
from collections import Counter

def rand6():
    return int(random.randint(1, 6))


def rand10():
    # 构造能被10整除个数的均匀分布随机数
    res = 0
    while True:
        res = (rand6() - 1) * 6 + rand6()  # 覆盖1到36的随机整数
        if res <= 30:
            break
    return res % 10 + 1


if __name__ == '__main__':
    resultList = []
    for _ in range(100000):
        resultList.append(rand10())

    count = Counter(resultList)
    print(count.most_common())


