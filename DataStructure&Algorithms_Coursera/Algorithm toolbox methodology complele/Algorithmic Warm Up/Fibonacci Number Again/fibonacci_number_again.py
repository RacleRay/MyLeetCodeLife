# python3


def fibonacci_number_again_naive(n, m):
    assert 0 <= n <= 10 ** 18 and 2 <= m <= 10 ** 3

    if n <= 1:
        return n

    previous, current = 0, 1
    for _ in range(n - 1):
        previous, current = current, (previous + current) % m

    return current


def fibonacci_number_again(n, m):
    assert 0 <= n <= 10 ** 18 and 2 <= m <= 10 ** 3

    def get_pisano_period(m):
        prev_prev, prev, curr = 0, 1, 1
        for i in range(m ** 2):
            curr = (prev_prev + prev) % m
            prev_prev = prev
            prev = curr
            if (prev_prev == 0 and prev == 1):
                return i + 1  # from begin, already 3 elements
    # print(n, m)

    reminder = n % get_pisano_period(m)
    # print(reminder)

    if reminder <= 1:
        return reminder

    prev = 0
    curr = 1
    for i in range(1, reminder):
        prev, curr = curr, (prev + curr) % m

    return curr



if __name__ == '__main__':
    input_n, input_m = map(int, input().split())
    print(fibonacci_number_again(input_n, input_m))
    print(fibonacci_number_again_naive(input_n, input_m))
