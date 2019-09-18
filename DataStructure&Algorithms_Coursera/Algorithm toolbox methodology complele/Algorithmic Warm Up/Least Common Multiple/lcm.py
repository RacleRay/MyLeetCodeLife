# python3


def lcm_naive(a, b):
    assert 1 <= a <= 2 * 10 ** 9 and 1 <= b <= 2 * 10 ** 9

    multiple = max(a, b)
    while multiple % a != 0 or multiple % b != 0:
        multiple += 1

    return multiple


def lcm(a, b):
    assert 1 <= a <= 2 * 10 ** 9 and 1 <= b <= 2 * 10 ** 9

    def gcp(a, b):
        max_ = max(a, b)
        min_ = min(a, b)

        reminder = max_ % min_
        if reminder == 0:
            return min_

        return gcp(min_, reminder)

    gcp_ = gcp(a, b)

    return a * b // gcp_


if __name__ == '__main__':
    input_a, input_b = map(int, input().split())
    print(lcm(input_a, input_b))
