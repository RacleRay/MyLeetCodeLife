# python3
import sys
import pysnooper


# @pysnooper.snoop()
def find_maximum_value(dataset):
    assert 1 <= len(dataset) <= 29

    if len(dataset) == 1:
        return dataset[0]

    def max_and_min(i, j):
        max_ = -sys.maxsize
        min_ = sys.maxsize
        for k in range(i, j):
            if ops[k] == '+':
                a = mat_max[i][k] + mat_max[k + 1][j]
                b = mat_max[i][k] + mat_min[k + 1][j]
                c = mat_min[i][k] + mat_max[k + 1][j]
                d = mat_min[i][k] + mat_min[k + 1][j]
            elif ops[k] == '-':
                a = mat_max[i][k] - mat_max[k + 1][j]
                b = mat_max[i][k] - mat_min[k + 1][j]
                c = mat_min[i][k] - mat_max[k + 1][j]
                d = mat_min[i][k] - mat_min[k + 1][j]
            else:
                a = mat_max[i][k] * mat_max[k + 1][j]
                b = mat_max[i][k] * mat_min[k + 1][j]
                c = mat_min[i][k] * mat_max[k + 1][j]
                d = mat_min[i][k] * mat_min[k + 1][j]

            max_ = max(max_, a, b, c, d)
            min_ = min(min_, a, b, c, d)

        return max_, min_

    elems = dataset[0: : 2]
    ops = dataset[1: -1: 2]
    length = len(elems)

    # from elems[i] to [j], the max and min matrix, only use a half
    mat_max = [[0] * length for _ in range(length)]
    mat_min = [[0] * length for _ in range(length)]

    # init diag
    for i in range(0, length):
        mat_max[i][i] = int(elems[i])
        mat_min[i][i] = int(elems[i])

    for s in range(1, length):
        for i in range(0, length - s):
            j = i + s
            mat_max[i][j], mat_min[i][j] = max_and_min(i, j)

    return mat_max[0][-1]


if __name__ == "__main__":
    print(type(find_maximum_value(input())))
    # print(find_maximum_value('5-8+7*4-8+9'))