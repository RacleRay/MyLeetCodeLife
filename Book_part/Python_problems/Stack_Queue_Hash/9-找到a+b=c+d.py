# python3
from collections import defaultdict


class Pair:
    def __init__(self, first=None, second=None):
        self.first = first
        self.second = second


def find_pair(input_array):
    sum_values_dict = defaultdict(Pair)
    length = len(input_array)

    first_index = 0
    while first_index < length:
        second_index = first_index + 1
        while second_index < length:
            sum_value = input_array[first_index] + input_array[second_index]

            # 成员变量不是None时，表示已经存在相等的数字对
            find_res = sum_values_dict[sum_value]
            if find_res.first is None:
                sum_values_dict[sum_value] = Pair(first_index, second_index)
            else:
                print("{} + {} = {} + {}".format(input_array[find_res.first],
                                                 input_array[find_res.second],
                                                 input_array[first_index],
                                                 input_array[second_index]))

            second_index += 1
        first_index += 1

    return None


if __name__ == "__main__":
    input_array = [3, 4, 7, 10, 20, 9, 8]
    find_pair(input_array)


