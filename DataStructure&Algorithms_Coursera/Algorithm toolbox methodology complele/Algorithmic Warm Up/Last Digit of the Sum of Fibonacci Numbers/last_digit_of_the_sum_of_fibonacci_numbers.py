# python3


def last_digit_of_the_sum_of_fibonacci_numbers_naive(n):
    assert 0 <= n <= 10 ** 18

    if n <= 1:
        return n

    fibonacci_numbers = [0] * (n + 1)
    fibonacci_numbers[0] = 0
    fibonacci_numbers[1] = 1
    for i in range(2, n + 1):
        fibonacci_numbers[i] = fibonacci_numbers[i - 2] + fibonacci_numbers[i - 1]

    return sum(fibonacci_numbers) % 10


def last_digit_of_the_sum_of_fibonacci_numbers(n):
    assert 0 <= n <= 10 ** 18

    n %= 60

    if n < 2:
        return n

    fib_last_digits = [0] * n + [0]
    fib_last_digits[1] = 1

    for i in range(2, n + 1):
        fib_last_digits[i] = (fib_last_digits[i - 1] + fib_last_digits[i - 2]) % 10

    # n %= 60
    #
    # prev = 0
    # curr = 1
    # res = 1
    # for i in range(n - 1):
    #     prev, curr = curr, (curr + prev) % 10
    #     res += curr

    return sum(fib_last_digits) % 10



if __name__ == '__main__':
    input_n = int(input())
    print(last_digit_of_the_sum_of_fibonacci_numbers(input_n))
