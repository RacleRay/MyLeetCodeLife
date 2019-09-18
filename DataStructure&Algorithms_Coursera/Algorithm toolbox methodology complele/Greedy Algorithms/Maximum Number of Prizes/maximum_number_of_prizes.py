# python3


def compute_optimal_summands(n):
    assert 1 <= n <= 10 ** 9
    summands = []

    # k = n
    # l = 1
    # while k > 2 * l:
    #     summands.append(l)
    #
    #     k -= l
    #     l += 1
    #
    # summands.append(k)

    if n <= 2:
        return [n]

    max_seq = int((-3 + (8 * n + 9) ** (0.5)) / 2)
    rest = int(n - max_seq * (max_seq + 1) / 2)

    if max_seq == rest:
        max_seq -= 1
        rest = int(n - max_seq * (max_seq + 1) / 2)

    summands = [i for i in range(1, max_seq + 1)]
    summands.append(rest)

    return summands


if __name__ == '__main__':
    input_n = int(input())
    output_summands = compute_optimal_summands(input_n)
    print(len(output_summands))
    print(" ".join(map(str, output_summands)))
