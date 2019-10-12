#Uses python3

import sys
import queue


def shortet_paths(adj, cost, s, distance, reachable, shortest):
    reachable_cycle = queue.Queue()
    distance[s] = 0
    reachable[s] = 1

    for _ in range(len(adj) - 1):
        for u in range(len(adj)):
            for v, weight in zip(adj[u], cost[u]):
                if distance[v] > distance[u] + weight:
                    distance[v] = distance[u] + weight
                    reachable[v] = 1

    for u in range(len(adj)):
        for v, weight in zip(adj[u], cost[u]):
            if distance[v] > distance[u] + weight:
                reachable_cycle.put(v)
                shortest[v] = 0

    bfs(adj, reachable_cycle, shortest)


def bfs(adj, reachable_queue, shortest_mark):
    # 搜索由负权环可达的节点，全部没有shortest path
    while not reachable_queue.empty():
        u = reachable_queue.get()
        for v in adj[u]:
            if shortest_mark[v] == 1:
                reachable_queue.put(v)
                shortest_mark[v] = 0


if __name__ == '__main__':
    # 6 7 1 2 10 2 3 5 1 3 100 3 5 7 5 4 10 4 3 -18 6 1 -1 1
    # 5 4 1 2 1 4 1 2 2 3 2 3 1 -5 4
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
    s = data[0]
    s -= 1
    distance = [float('inf')] * n
    reachable = [0] * n
    shortest = [1] * n
    shortet_paths(adj, cost, s, distance, reachable, shortest)
    for x in range(n):
        if reachable[x] == 0:
            print('*')
        elif shortest[x] == 0:
            print('-')
        else:
            print(distance[x])

