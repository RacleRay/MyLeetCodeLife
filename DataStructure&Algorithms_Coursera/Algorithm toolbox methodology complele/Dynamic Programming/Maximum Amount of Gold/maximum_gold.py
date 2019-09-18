# python3

from sys import stdin
import pysnooper

# @pysnooper.snoop()
def maximum_gold(capacity, weights):
    assert 1 <= capacity <= 10 ** 4
    assert 1 <= len(weights) <= 10 ** 3
    assert all(1 <= w <= 10 ** 5 for w in weights)

    table = [[0] * (capacity + 1) for _ in range(2)]

    for i in range(1, len(weights) + 1):
        for j in range(1, capacity + 1):
            k = (i - 1) % 2  # 只使用两行的trick
            max_ = table[k][j]
            if weights[i - 1] <= j:
                with_i = table[k][j - weights[i - 1]] + weights[i - 1]
                max_ = max(with_i, max_)

            table[i % 2][j] = max_

    return table[len(weights) % 2][-1]


if __name__ == '__main__':
    # input_capacity, n, *input_weights = list(map(int, stdin.read().split()))
    # assert len(input_weights) == n
    #
    # print(maximum_gold(input_capacity, input_weights))
    print(maximum_gold(20, (5, 7, 12, 18)))
