# python3
# import pysnooper

def build_heap_naive(data):
    """Build a heap from ``data`` inplace.

    Returns a sequence of swaps performed by the algorithm.
    """
    # The following naive implementation just sorts the given sequence
    # using selection sort algorithm and saves the resulting sequence
    # of swaps. This turns the given array into a heap, but in the worst
    # case gives a quadratic number of swaps.
    #
    # TODO: replace by a more efficient implementation
    swaps = []
    for i in range(len(data)):
        for j in range(i + 1, len(data)):
            if data[i] > data[j]:
                swaps.append((i, j))
                data[i], data[j] = data[j], data[i]
    return swaps


def build_heap(data):
    size = len(data)
    swaps = []

    # @pysnooper.snoop()
    def _shiftdown(i):
        """min heap"""
        min_index = i
        left_child = 2 * i + 1
        right_child = 2 * i + 2

        if left_child <= size - 1 and data[left_child] < data[min_index]:
            swap = (i, left_child)
            min_index = left_child

        if right_child <= size - 1 and data[right_child] < data[min_index]:
            swap = (i, right_child)
            min_index = right_child

        if min_index == i:
            return
        else:
            data[i], data[min_index] = data[min_index], data[i]
            swaps.append(swap)
            _shiftdown(min_index)

    for i in range((size - 1) // 2, -1, -1):
        _shiftdown(i)

    return swaps


def main():
    n = int(input())
    data = list(map(int, input().split()))
    assert len(data) == n

    swaps = build_heap(data)

    print(len(swaps))
    for i, j in swaps:
        print(i, j)


if __name__ == "__main__":
    main()
