#Uses python3

import sys
import queue

def bipartite(adj):
    dist = [-1 for i in range(len(adj))]
    dist[0] = 0

    q = queue.Queue()
    q.put(0)

    while not q.empty():
        u = q.get()
        for v in adj[u]:
            if dist[v] == -1:
                q.put(v)
                dist[v] = dist[u] + 1
            # 检测是否存在相同dfs距离的节点是相连的
            for child_of_v in adj[v]:
                if dist[child_of_v] == dist[v]:
                    return 0

    return 1

if __name__ == '__main__':
    # 5 4 5 2 4 2 3 4 1 4
    input = sys.stdin.read()
    data = list(map(int, input.split()))
    n, m = data[0:2]
    data = data[2:]
    edges = list(zip(data[0:(2 * m):2], data[1:(2 * m):2]))
    adj = [[] for _ in range(n)]
    for (a, b) in edges:
        adj[a - 1].append(b - 1)
        adj[b - 1].append(a - 1)
    print(bipartite(adj))
