# python3
from sys import stdin
from bisect import bisect_left, bisect_right
from itertools import chain


def points_cover_naive(starts, ends, points):
    assert len(starts) == len(ends)
    count = [0] * len(points)

    for index, point in enumerate(points):
        for start, end in zip(starts, ends):
            if start <= point <= end:
                count[index] += 1

    return count


def points_cover(starts, ends, points):
    count = {}
    seg_cover_num = 0

    # 标记三种点：注意，考虑三种点的优先级，算法是从左到右的遍历
    listpoints = [(x, 1) for x in starts]
    listpoints += [(x, 2) for x in points]
    listpoints += [(x, 3) for x in ends]

    listpoints.sort()

    for p in listpoints:
        if p[1] == 1:
            seg_cover_num += 1
        elif p[1] == 3:
            seg_cover_num -= 1
        elif p[1] == 2:
            count[p[0]] = seg_cover_num

    res = [count[i] for i in points]

    return res

    # time limit
    # count = [0] * len(points)
    # segments = [i for i in zip(starts, ends)]
    # segments.sort()
    #
    # def find_first_seg(segments, point):
    #     left = 0
    #     right = len(segments) - 1
    #     while left <= right:
    #         mid = (left + right) // 2
    #         # 检查二分条件
    #         # mid是第一个包含point的segment
    #         if (segments[mid][0] <= point and segments[mid][1] >= point):
    #             if mid == 0 or (segments[mid - 1][1] < point):
    #                 return mid
    #             # mid和mid - 1都是包含point的segment
    #             elif (segments[mid -1 ][0] <= point and segments[mid - 1][1] >= point):
    #                 right = mid - 1
    #         # mid不包含point，且point在左侧
    #         if segments[mid][0] > point:
    #             right = mid - 1
    #         # mid不包含point，且point在右侧
    #         elif segments[mid][1] < point:
    #             left = mid + 1
    #
    #     return -1

    # def find_last_seg(segments, point):
    #     left = 0
    #     right = len(segments) - 1
    #     while left <= right:
    #         mid = (left + right) // 2
    #         # 检查二分条件
    #         # mid是最后一个包含point的segment
    #         if (segments[mid][0] <= point and segments[mid][1] >= point):
    #             if mid == len(segments) - 1 or (segments[mid + 1][0] > point):
    #                 return mid
    #             # mid和mid + 1都是包含point的segment
    #             elif (segments[mid +1 ][0] <= point and segments[mid + 1][1] >= point):
    #                 left = mid + 1
    #         # mid不包含point，且point在右侧
    #         if segments[mid][1] < point:
    #             left = mid + 1
    #         # mid不包含point，且在point在左侧
    #         elif segments[mid][0] > point:
    #             right = mid - 1
    #
    #     return -1

    # for i in range(len(points)):
    #     first_seg = find_first_seg(segments, points[i])
    #
    #     if first_seg == -1:
    #         continue
    #     else:
    #         more_seq = 0
    #         for next in segments[first_seg + 1: ]:
    #             if next[0] <= points[i] and next[1] >= points[i]:
    #                 more_seq += 1
    #             elif next[0] > points[i]:
    #                 break
    #         count[i] = 1 + more_seq
    #
    # return count


if __name__ == '__main__':
    # data = list(map(int, stdin.read().split()))
    # n, m = data[0], data[1]
    # input_starts, input_ends = data[2:2 * n + 2:2], data[3:2 * n + 2:2]
    # input_points = data[2 * n + 2:]
    #
    # output_count = points_cover(input_starts, input_ends, input_points)
    # print(" ".join(map(str, output_count)))

    output_count = points_cover([1, 6], [5, 10], [1, 4, 4, 4, 11])
    print(" ".join(map(str, output_count)))
