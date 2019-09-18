# python3
from collections import namedtuple
from itertools import combinations
import sys
from math import sqrt


Point = namedtuple('Point', 'x y')


def distance_squared(first_point, second_point):
    return (first_point.x - second_point.x) ** 2 + (first_point.y - second_point.y) ** 2


def minimum_distance_squared_naive(points):
    min_distance_squared = float("inf")

    for p, q in combinations(points, 2):
        min_distance_squared = min(min_distance_squared,
                                   distance_squared(p, q))

    return min_distance_squared


def minimum_distance_squared(points):
    # assert len(points) > 1

    # points.sort()
    print(points)
    x_sort = sorted(points, key=lambda i: i.x)
    y_sort = sorted(points, key=lambda i: i.y)

    def _compute(x_sort, y_sort):
        def distance(point1, point2):
            # 只进行比较时，不用开方，最后输出再开方
            return ((point1.x - point2.x) ** 2 + (point1.y - point2.y) ** 2)

        if len(x_sort) < 2:
            return float('inf')
        if len(x_sort) == 2:
            return distance(x_sort[0], x_sort[-1])

        mid = (len(x_sort) - 1) // 2
        split_line = (x_sort[mid].x + x_sort[mid + 1].x) / 2

        y_left = [p for p in y_sort if p.x <= x_sort[mid].x]
        y_right = [p for p in y_sort if p.x > x_sort[mid].x]

        min_set1 = _compute(x_sort[: mid + 1], y_left)
        min_set2 = _compute(x_sort[mid + 1: ], y_right)
        min_ = min(min_set1, min_set2)

        closeY = []
        for point in y_sort:
            if abs(point.x - split_line) <= min_:
                closeY.append(point)

        closestY = min_
        if len(closeY) > 1:
            for i in range(len(closeY) - 1):
                for j in range(i + 1, min(i + 8, len(closeY))):
                    closestY = min(distance(closeY[i], closeY[j]), closestY)

            return closestY
        else:
            return min_


        # for i in range(len(candidate_set)):
        #     j = i + 1
        #     while j < len(candidate_set) and \
        #             candidate_set[j].y - candidate_set[i].y < min_:
        #         min_ = min(distance(candidate_set[i], candidate_set[j]), min_)
        #         j += 1
        #
        # return min_
    a = _compute(x_sort, y_sort)
    # print(a)
    return a



if __name__ == '__main__':
    # input_n = int(input())
    input_points = []
    # for _ in range(input_n):
    #     x, y = map(int, input().split())
    #     input_point = Point(x, y)
    #     input_points.append(input_point)

    a = [(-1,2),(-2,-2),(-1,-2),(3,1),(-2,1)]
    for x, y in a:
        input_point = Point(x, y)
        input_points.append(input_point)

    print("{0:.9f}".format(sqrt(minimum_distance_squared(input_points))))


# def minimum_distance(x, y):
#     points = []
#     for i in range(len(x)):
#         input_point = Point(x[i], y[i])
#         points.append(input_point)
#
#     x_sort = sorted(points, key=lambda i: i.x)
#     y_sort = sorted(points, key=lambda i: i.y)
#
#     def _compute(x_sort, y_sort):
#         def distance(point1, point2):
#             # 只进行比较时，不用开方，最后输出再开方
#             return ((point1.x - point2.x) ** 2 + (point1.y - point2.y) ** 2)
#
#         if len(x_sort) < 2:
#             return float('inf')
#
#         if len(x_sort) == 2:
#             return distance(x_sort[0], x_sort[1])
#
#         mid = (len(x_sort) - 1) // 2
#         split_line = (x_sort[mid - 1].x + x_sort[mid].x) / 2
#
#         y_left = [p for p in y_sort if p.x <= x_sort[mid].x]
#         y_right = [p for p in y_sort if p.x > x_sort[mid].x]
#
#         min_set1 = _compute(x_sort[: mid + 1], y_left)
#         min_set2 = _compute(x_sort[mid + 1: ], y_right)
#         min_ = min(min_set1, min_set2)
#
#         closeY = []
#         for point in y_sort:
#             if abs(point.x - split_line) <= min_:
#                 closeY.append(point)
#
#         if len(closeY) > 1:
#             for i in range(len(closeY) - 1):
#                 for j in range(i + 1, min(i + 8, len(closeY))):
#                     closestY = min(distance(closeY[i], closeY[j]), min_)
#
#             return closestY
#         else:
#             return min_
#
#     return sqrt(_compute(x_sort, y_sort))
#
# if __name__ == '__main__':
#     input = sys.stdin.read()
#     data = list(map(int, input.split()))
#     n = data[0]
#     x = data[1::2]
#     y = data[2::2]
#     print("{0:.9f}".format(minimum_distance(x, y)))
