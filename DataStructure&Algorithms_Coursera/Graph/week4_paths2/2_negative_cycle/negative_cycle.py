#Uses python3

import sys
# from math import log

def negative_cycle(adj, cost):
    dist = [float('inf') for _ in range(len(adj))]
    # prev = [None for _ in range(len(adj))]
    dist[0] = 0

    for _ in range(len(adj) - 1):
        for u in range(len(adj)):
            for v, weight in zip(adj[u], cost[u]):
                if dist[v] > dist[u] + weight:  # 假如不是同一个连通图，不会更新
                    dist[v] = dist[u] + weight
                # 在新子图中
                if dist[v] == float('inf') and dist[u] == float('inf'):
                    dist[u] = 0
                    dist[v] = weight

    for u in range(len(adj)):
        for v, weight in zip(adj[u], cost[u]):
            if dist[v] > dist[u] + weight:
                return 1

    return 0


if __name__ == '__main__':
    # 4 4 1 2 -5 4 1 2 2 3 2 3 1 1
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
    print(negative_cycle(adj, cost))
