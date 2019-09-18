# python3

from itertools import permutations


def largest_number_naive(numbers):
    numbers = list(map(str, numbers))

    largest = 0

    for permutation in permutations(numbers):
        largest = max(largest, int("".join(permutation)))

    return largest


def largest_number(numbers):

    def is_better(num1, num2):
        max_len = max(len(str(num1)), len(str(num2)))
        num1 = str(num1) * (max_len // len(str(num1)))
        num2 = str(num2) * (max_len // len(str(num2)))
        return num1 > num2

    salary = ''
    while len(numbers) > 0:
        better_number = -1
        for i in numbers:
            if is_better(i, better_number):
                better_number = i
        salary += str(better_number)
        numbers.remove(better_number)

    return salary


if __name__ == '__main__':
    n = int(input())
    input_numbers = input().split()
    assert len(input_numbers) == n
    print(largest_number(input_numbers))
