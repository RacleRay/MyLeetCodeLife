#Uses python3
import sys
import math


class DisjointSet:
    def __init__(self, n):
        # 初始单个点为一个集合
        self.cluster = n
        self.parents = list(range(n))  # 指向自身
        self.rank = [0] * n  # 最优union所用参数

    def find(self, i):
        """find root and compress path"""
        if self.parents[i] != i:
            self.parents[i] = self.find(self.parents[i])  # 父节点的父节点
        return self.parents[i]

    def union(self, x, y):
        rootx = self.find(x)
        rooty = self.find(y)
        if rootx != rooty:
            if self.rank[rootx] > self.rank[rooty]:  # rank低的，将root指向rank高的root
                self.parents[rooty] = rootx
            elif self.rank[rootx] < self.rank[rooty]:
                self.parents[rootx] = rooty
            else:
                self.parents[rooty] = rootx  # 相同rank节点，合并并增加rank
                self.rank[rootx] += 1
            self.cluster -= 1


def distance(p1, p2):
    return math.hypot((p1[0] - p2[0]), (p1[1] - p2[1]))

def clustering(x, y, k):
    nodes = list(zip(x, y))
    v_set = DisjointSet(len(nodes))

    weights = [((i, j), distance(nodes[i], nodes[j]))
                for i in range(len(nodes)) for j in range(i + 1, len(nodes))]
    weights.sort(key=lambda x: x[1])

    while len(weights) > 0:
        (v, u), weight = weights.pop(0)

        if v_set.find(v) != v_set.find(u):
            if v_set.cluster == k:  # 在形成k个cluster之后，下条边就是最大的d的值
                return weight
            v_set.union(v, u)

    return -1.


if __name__ == '__main__':
    # 12 7 6 4 3 5 1 1 7 2 7 5 7 3 3 7 8 2 8 4 4 6 7 2 6 3
    # 8 3 1 1 2 4 6 9 8 9 9 8 9 3 11 4 12 4
    input = sys.stdin.read()
    data = list(map(int, input.split()))
    n = data[0]
    data = data[1:]
    x = data[0:2 * n:2]
    y = data[1:2 * n:2]
    data = data[2 * n:]
    k = data[0]
    print("{0:.9f}".format(clustering(x, y, k)))
