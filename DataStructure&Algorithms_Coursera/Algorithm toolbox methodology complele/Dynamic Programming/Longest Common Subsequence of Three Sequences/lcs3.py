# python3


def lcs3(first_sequence, second_sequence, third_sequence):
    assert len(first_sequence) <= 100
    assert len(second_sequence) <= 100
    assert len(third_sequence) <= 100

    table = [[[0] * (len(third_sequence) + 1) for _ in range((len(second_sequence) + 1))] \
             for _ in range(len(first_sequence) + 1)]

    for i in range(1, len(first_sequence) + 1):
        for j in range(1, len(second_sequence) + 1):
            for k in range(1, len(third_sequence) + 1):
                if first_sequence[i - 1] == second_sequence[j - 1] == third_sequence[k - 1]: # i, j, k从1开始
                    table[i][j][k] = table[i -1][j - 1][k - 1] + 1
                else:
                    table[i][j][k] = max(table[i][j - 1][k],
                                         table[i - 1][j][k],
                                         table[i][j][k - 1])

    return table[-1][-1][-1]


if __name__ == '__main__':
    n = int(input())
    a = list(map(int, input().split()))
    assert len(a) == n

    m = int(input())
    b = list(map(int, input().split()))
    assert len(b) == m

    q = int(input())
    c = list(map(int, input().split()))
    assert len(c) == q

    print(lcs3(a, b, c))
