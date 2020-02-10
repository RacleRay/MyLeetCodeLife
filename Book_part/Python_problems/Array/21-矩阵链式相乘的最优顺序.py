# python3


def matrixOrder(dims, left, right):
    """第i个矩阵的维度为dims[i-1] * dims[i]"""
    if left == right:
        return 0

    min_times = float("inf")
    seperator = left
    while seperator < right:
        mul_times = matrixOrder(dims, left, seperator) + \
            matrixOrder(dims, seperator + 1, right) + \
            dims[left - 1] * dims[seperator] * dims[right]
        if mul_times < min_times:
            min_times = mul_times
        seperator += 1

    return min_times


def matrixOrder2(dims):
    n = len(dims)
    cost_table = [[None for _ in range(n)] for _ in range(n)]

    # 只有一个矩阵时不需要计算
    i = 1
    while i < n:
        cost_table[i][i] = 0
        i += 1

    num_of_matrix = 2
    while num_of_matrix < n:
        from_ = 1
        while from_ < n - num_of_matrix + 1:
            to_ = from_ + num_of_matrix - 1
            cost_table[from_][to_] = float('inf')
            mid_ = from_
            while mid_ < to_:
                cost = cost_table[from_][mid_] + cost_table[mid_ + 1][to_] + \
                    dims[from_ - 1] * dims[mid_] * dims[to_]
                if cost < cost_table[from_][to_]:
                    cost_table[from_][to_] = cost
                mid_ += 1
            from_ += 1
        num_of_matrix += 1

    # 从第一个matrix到最后一个matrix的最小乘法次数
    return cost_table[1][n - 1]

if __name__ == "__main__":
    dims = [1, 5, 2, 4, 6]
    print("Result is: ", matrixOrder(dims, 1, len(dims) - 1))

    print("Result is: ", matrixOrder2(dims))
