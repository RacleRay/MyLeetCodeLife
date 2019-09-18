# python3


def linear_search(keys, query):
    for i in range(len(keys)):
        if keys[i] == query:
            return i

    return -1


def binary_search(keys, query):
    assert all(keys[i] < keys[i + 1] for i in range(len(keys) - 1))
    # assert 1 <= len(keys) <= 10 ** 4

    minIndex = 0
    maxIndex = len(keys) - 1

    while maxIndex >= minIndex:
        midIndex = (minIndex + maxIndex) // 2
        if keys[midIndex] == query:
            return midIndex
        elif keys[midIndex] > query:
            maxIndex = midIndex - 1
        else:
            minIndex = midIndex + 1

    return -1

    # res = [-1] * len(query)
    #
    # for i in range(len(query)):
    #     m = binary_search_single(keys, query[i])
    #     res[i] = m
    #
    # return res


if __name__ == '__main__':
    input_n = int(input())
    input_keys = list(map(int, input().split()))
    assert len(input_keys) == input_n
    input_m = int(input())
    input_queries = list(map(int, input().split()))
    assert len(input_queries) == input_m

    for q in input_queries:
        print(binary_search(input_keys, q), end=' ')
