# python3

from random import randint


def partition3(array, left, right):

    def _swap(array, i, j):
        array[i], array[j] = array[j], array[i]

    pivot = array[left]

    # init for loop
    if array[left] > array[right]:
        _swap(array, left, right)

    # init
    less_pivot = left      # 小于p部分，最右边的下一个index
    greater_pivot = right  # 大于p部分，最左边的index
    curr = left            # 等于p部分，最右边的下一个index

    while curr <= greater_pivot:

        if array[curr] < pivot:
            _swap(array, less_pivot, curr)
            less_pivot += 1
            curr += 1

        elif array[curr] == pivot:
            curr += 1

        else:
            _swap(array, greater_pivot, curr)
            greater_pivot -= 1

    return less_pivot - 1, curr

def randomized_quick_sort(array, left, right):
    if left >= right:
        return
    k = randint(left, right)
    array[left], array[k] = array[k], array[left]

    m1, m2 = partition3(array, left, right)

    randomized_quick_sort(array, left, m1)
    randomized_quick_sort(array, m2, right)

    return array


if __name__ == '__main__':
    input_n = int(input())
    elements = list(map(int, input().split()))
    assert len(elements) == input_n
    randomized_quick_sort(elements, 0, len(elements) - 1)
    print(" ".join(map(str, elements)))
