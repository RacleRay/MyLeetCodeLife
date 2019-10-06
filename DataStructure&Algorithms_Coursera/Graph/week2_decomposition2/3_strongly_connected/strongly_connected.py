#Uses python3

import sys

sys.setrecursionlimit(200000)


def number_of_strongly_connected_components(adj):
    adj_inverse = [[] for _ in range(len(adj))]
    for i, v in enumerate(adj):
        for v_ in v:
            adj_inverse[v_].append(i)

    def explore(adj, x):
        visited[x] = 1  # mark visited
        for v_next in adj[x]:
            if not visited[v_next] and len(adj[v_next]) != 0:
                explore(adj, v_next)

    def exploreForOrder(adj, v):
        visited[v] = 1
        for v_next in adj[v]:
            if not visited[v_next]:
                exploreForOrder(adj, v_next)
        order.append(v)

    visited = [0] * len(adj)
    order = [0] * len(adj)
    for v in range(len(adj_inverse)):
        if not visited[v]:
            exploreForOrder(adj_inverse, v)

    result = 0
    visited = [0] * len(adj)
    order.reverse()
    for v in order:
        if not visited[v]:
            explore(adj, v)
            result += 1

    return result


if __name__ == '__main__':
    # 4 4 1 2 4 1 2 3 3 1
    # 5 7 2 1 3 2 3 1 4 3 4 1 5 2 5 3
    # 4 3 1 2 3 2 4 3
    # 100 100 27 96 23 51 42 10 40 22 30 41 80 40 13 70 21 94 88 35 38 86 53 83 71 84 64 26 4 46 76 43 24 76 26 83 18 75 42 98 36 39 47 63 33 96 89 54 47 80 95 8 34 41 91 45 78 1 12 74 2 37 98 81 30 32 93 30 45 71 38 44 85 18 89 10 71 35 73 52 28 42 98 20 22 69 56 79 78 63 53 58 77 13 6 11 56 36 4 11 92 63 32 78 71 24 16 79 66 89 72 6 20 15 2 91 100 75 93 7 42 100 18 88 49 75 33 78 81 1 42 95 73 64 50 66 33 68 14 38 80 89 8 16 87 18 20 80 81 38 14 35 91 20 36 5 16 8 61 11 72 91 26 57 60 83 80 11 58 1 71 36 41 30 57 46 47 82 46 74 28 9 76 70 69 58 39 73 89 55 93 54 17 92 54 44 21 69 87 58 96 34
    input = '100 100 27 96 23 51 42 10 40 22 30 41 80 40 13 70 21 94 88 35 38 86 53 83 71 84 64 26 4 46 76 43 24 76 26 83 18 75 42 98 36 39 47 63 33 96 89 54 47 80 95 8 34 41 91 45 78 1 12 74 2 37 98 81 30 32 93 30 45 71 38 44 85 18 89 10 71 35 73 52 28 42 98 20 22 69 56 79 78 63 53 58 77 13 6 11 56 36 4 11 92 63 32 78 71 24 16 79 66 89 72 6 20 15 2 91 100 75 93 7 42 100 18 88 49 75 33 78 81 1 42 95 73 64 50 66 33 68 14 38 80 89 8 16 87 18 20 80 81 38 14 35 91 20 36 5 16 8 61 11 72 91 26 57 60 83 80 11 58 1 71 36 41 30 57 46 47 82 46 74 28 9 76 70 69 58 39 73 89 55 93 54 17 92 54 44 21 69 87 58 96 34'
    data = list(map(int, input.split()))
    n, m = data[0:2]
    data = data[2:]
    edges = list(zip(data[0:(2 * m):2], data[1:(2 * m):2]))
    adj = [[] for _ in range(n)]
    for (a, b) in edges:
        adj[a - 1].append(b - 1)
    print(number_of_strongly_connected_components(adj))
