# python3

from itertools import product
from sys import stdin
import pysnooper

# @pysnooper.snoop()
def partition3(values):
    assert 1 <= len(values) <= 20
    assert all(1 <= v <= 30 for v in values)

    total = sum(values)
    if total % 3 != 0:
        return 0

    # 0，1：当前value array中，是否含有等于某个值的子序列
    table = [[0] * (2 * total // 3 + 1) for _ in range(len(values) + 1)]
    for i in range(len(values) + 1):
        table[i][0] = 1

    get_sum_3 = 0
    for i in range(1, len(values) + 1):
        for j in range(1, 2 * total // 3 + 1):
            table[i][j] = table[i - 1][j]  # 不包含value[i-1]
            if values[i - 1] <= j:
                temp = table[i - 1][j - values[i - 1]]  # 包含value[i-1]
                table[i][j] = temp or table[i][j]

            if j == 2 * total // 3:
                get_sum_3 = table[i][j]

    # 同时能得到 sum / 3 和 2 * sum /3
    return get_sum_3 and table[-1][-1]


if __name__ == '__main__':
    # input_n, *input_values = list(map(int, stdin.read().split()))
    # assert input_n == len(input_values)
    print(partition3([3, 3, 3]))
