#Uses python3

import sys
import queue


def distance(adj, cost, s, t):
    dist = [float('inf') for _ in range(len(adj))]
    dist[s] = 0

    minHeap = queue.PriorityQueue()
    for v, dist_value in enumerate(dist):
        minHeap.put((v, dist_value))

    while not minHeap.empty():
        u, d = minHeap.get()
        # 因为minHeap.put((v, dist[v]))，直接将新值加入，原来的元素仍在
        if u != s and dist[u] < d:
            continue

        for v, weight in zip(adj[u], cost[u]):
            if dist[v] > dist[u] + weight:
                dist[v] = dist[u] + weight
                minHeap.put((v, dist[v]))

    return -1 if dist[t] == float('inf') else dist[t]


if __name__ == '__main__':
    # 4 4 1 2 1 4 1 2 2 3 2 1 3 5 1 3
    # 5 9 1 2 4 1 3 2 2 3 2 3 2 1 2 4 2 3 5 4 5 4 1 2 5 3 3 4 4 1 5
    # 3 3 1 2 7 1 3 5 2 3 2 3 2
    input = sys.stdin.read()
    data = list(map(int, input.split()))
    n, m = data[0:2]
    data = data[2:]
    edges = list(zip(zip(data[0:(3 * m):3], data[1:(3 * m):3]), data[2:(3 * m):3]))
    data = data[3 * m:]
    adj = [[] for _ in range(n)]
    cost = [[] for _ in range(n)]
    for ((a, b), w) in edges:
        adj[a - 1].append(b - 1)
        cost[a - 1].append(w)
    s, t = data[0] - 1, data[1] - 1
    print(distance(adj, cost, s, t))
