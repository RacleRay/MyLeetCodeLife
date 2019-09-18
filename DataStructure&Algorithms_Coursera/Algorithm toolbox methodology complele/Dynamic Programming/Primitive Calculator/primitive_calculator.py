# python3


def compute_operations(n):
    assert 1 <= n <= 10 ** 6

    optimal = [(0, 1)]  # minimum number of operations needed to get n from 1, itermediate numbers.

    for i in range(1, n + 1):
        min_ = optimal[i - 1][0] + 1
        min_and_prev = ((min_, i - 1))

        if i % 2 == 0:
            min_2 = optimal[i // 2][0] + 1
            if min_2 < min_:
                min_ = min_2
                min_and_prev = (min_, i // 2)

        if i % 3 == 0:
            min_3 = optimal[i // 3][0] + 1
            if min_3 < min_:
                min_ = min_3
                min_and_prev = (min_, i // 3)

        optimal.append(min_and_prev)

    trace = n
    res = [n]
    while trace > 1:
        trace = optimal[trace][1]
        res.insert(0, trace)

    return res


if __name__ == '__main__':
    input_n = int(input())
    output_sequence = compute_operations(input_n)
    # print(output_sequence)
    print(len(output_sequence) - 1)
    print(" ".join(map(str, output_sequence)))
