# python3
import pysnooper


def memoize(f):
    memo = {}
    def helper(s1, s2):
        if (s1, s2) not in memo:
            memo[(s1, s2)] = f(s1, s2)
        return memo[(s1, s2)]
    return helper

# @pysnooper.snoop(watch='min_')
@memoize
def edit_distance(first_string, second_string):
    if len(first_string) == 0 or len(second_string) == 0:
        return len(first_string) or len(second_string)

    min_ = edit_distance(first_string[: -1], second_string[: -1])
    if first_string[-1] != second_string[-1]:
         min_ += 1

    min_ = min(edit_distance(first_string[: -1], second_string) + 1,
               edit_distance(first_string, second_string[: -1]) + 1,
               min_)

    return min_

if __name__ == "__main__":
    # print(edit_distance(input(), input()))
    print(edit_distance('short', 'ports'))
