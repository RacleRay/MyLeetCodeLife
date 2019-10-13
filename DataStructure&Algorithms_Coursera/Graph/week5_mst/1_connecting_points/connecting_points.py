#Uses python3
import sys
import math
import queue
# import itertools


def minimum_distance(x, y):
    result = 0.
    nodes = [(x_, y_) for x_, y_ in zip(x, y)]
    # edges = itertools.combinations(nodes, 2)

    cost = [float('inf') for _ in range(len(nodes))]
    parents = [None for _ in range(len(nodes))]
    mark = [0] * len(nodes)

    cost[0] = 0

    prio_q = queue.PriorityQueue()
    prio_q.put((0, 0))

    while not prio_q.empty():
        cost_v, v= prio_q.get()
        if mark[v] == 1:  # prim算法的防止成环措施
            continue
        mark[v] = 1
        result += cost_v

        for z in range(len(nodes)):
            if mark[z] == 0:
                d = distance(nodes[v], nodes[z])
                if cost[z] > d:
                    cost[z] = d
                    parents[z] = v
                    prio_q.put((cost[z], z))

    return result

def distance(p1, p2):
    return math.sqrt((p1[0] - p2[0]) ** 2 + (p1[1] - p2[1]) ** 2)

if __name__ == '__main__':
    # 5 0 0 0 2 1 1 3 0 3 2
    # 4 0 0 0 1 1 0 1 1
    input = sys.stdin.read()
    data = list(map(int, input.split()))
    n = data[0]
    x = data[1::2]
    y = data[2::2]
    print("{0:.9f}".format(minimum_distance(x, y)))
