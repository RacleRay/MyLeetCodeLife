"""
在二维空间里给定一些 points 和一个 origin，从 points 中找到 k 个离 origin 欧几里得距离最近的点。按照欧几里得距离由小到大返回。
如果 两个点有相同欧几里得距离，则按照x值来排序；若x值也相同，就再按照y值排序
"""

# O(nlogn) 的算法也是可以通过的, 但能否有 O(nlogk) 的解决方案

from dataclasses import dataclass
import heapq

@dataclass
class Point:
    x: int
    y: int

def k_closest(points, origin, k):
    heap = []
    for point in points:
        dist = get_distance(point, origin)
        heapq.heappush(heap, (-dist, -point.x, -point.y))
        if len(heap) > k:
            heapq.heappop(heap)

    ret = []
    while len(heap) > 0:
        _, x, y = heapq.heappop(heap)
        ret.append(Point(-x, -y))
    ret.reverse()
    return ret


def get_distance(a, b):
    return (a.x - b.x) ** 2 + (a.y - b.y) ** 2