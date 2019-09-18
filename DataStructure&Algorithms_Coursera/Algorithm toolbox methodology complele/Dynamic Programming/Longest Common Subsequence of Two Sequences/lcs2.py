# python3


def lcs2(first_sequence, second_sequence):
    assert len(first_sequence) <= 100
    assert len(second_sequence) <= 100

    table = [[0] * (len(second_sequence) + 1) \
             for _ in range(len(first_sequence) + 1)]

    for i in range(1, len(first_sequence) + 1):
        for j in range(1, len(second_sequence) + 1):
            if first_sequence[i - 1] == second_sequence[j - 1]: # i, j从1开始
                table[i][j] = table[i -1][j - 1] + 1
            if first_sequence[i - 1] != second_sequence[j -1]:
                table[i][j] = max(table[i][j - 1],
                                  table[i - 1][j])

    return table[-1][-1]



if __name__ == '__main__':
    n = int(input())
    a = list(map(int, input().split()))
    assert len(a) == n

    m = int(input())
    b = list(map(int, input().split()))
    assert len(b) == m

    print(lcs2(a, b))
