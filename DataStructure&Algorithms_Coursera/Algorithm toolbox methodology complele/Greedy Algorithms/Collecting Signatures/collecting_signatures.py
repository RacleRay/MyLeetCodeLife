# python3

from collections import namedtuple
from sys import stdin

Segment = namedtuple('Segment', 'start end')


def compute_optimal_points(segments):
    if len(segments) == 0:
        return 0

    sort_seg = sorted(segments, key=lambda x: x.start)

    # init
    result = set()
    max_coord = sort_seg[0].end
    for seg in sort_seg[1: ]:

        if seg.start <= max_coord and seg.end >= max_coord:
            continue
        if seg.start <= max_coord and seg.end < max_coord:
            max_coord = seg.end

        if seg.start > max_coord:
            result.add(max_coord)
            max_coord = seg.end

    result.add(max_coord)

    return result



if __name__ == '__main__':
    n, *data = map(int, stdin.read().split())
    input_segments = list(map(lambda x: Segment(x[0], x[1]), zip(data[::2], data[1::2])))
    assert n == len(input_segments)
    output_points = compute_optimal_points(input_segments)
    print(len(output_points))
    print(" ".join(map(str, output_points)))
