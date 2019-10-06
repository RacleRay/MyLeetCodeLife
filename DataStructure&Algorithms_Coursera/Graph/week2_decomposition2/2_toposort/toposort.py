#Uses python3

import sys

def dfs(adj, used, sub_order, x):

    def explore(vertice):
        used[vertice] = 1
        for v_next in adj[vertice]:
            if used[v_next] == 0:
                explore(v_next)
        sub_order.append(vertice)
        return sub_order

    sub_order = explore(x)
    return sub_order


def toposort(adj):
    used = [0] * len(adj)
    order = []

    for i in range(len(adj)):
        if len(adj[i]) != 0 and used[i] == 0:
            sub_order = []
            sub_order = dfs(adj, used, sub_order, i)
            order.extend(sub_order)

    for i in range(len(adj)):
        if used[i] == 0:
            order.append(i)

    order.reverse()
    return order

if __name__ == '__main__':
    # 5 7 2 1 3 2 3 1 4 3 4 1 5 2 5 3
    # 4 3 1 2 4 1 3 1
    # 5 10 4 5 3 1 2 1 2 3 5 1 2 5 4 1 2 4 3 4 3 5
    input = sys.stdin.read()
    data = list(map(int, input.split()))
    n, m = data[0:2]
    data = data[2:]
    edges = list(zip(data[0:(2 * m):2], data[1:(2 * m):2]))
    adj = [[] for _ in range(n)]
    for (a, b) in edges:
        adj[a - 1].append(b - 1)
    order = toposort(adj)
    for x in order:
        print(x + 1, end=' ')

