#Uses python3

import sys


def number_of_components(adj):
    graph_num = 1
    visited = [0 for _ in range(len(adj))]
    subgraphs = {}

    def explore(adj, x, graph_num):
        visited[x] = 1
        subgraphs[graph_num] = {x}
        for neighbor in adj[x]:
            if visited[neighbor] == 0:
                subgraphs[graph_num].add(neighbor)
                explore(adj, neighbor, graph_num)

    for i in range(len(adj)):
        if visited[i] == 0:
            explore(adj, i, graph_num)
            graph_num += 1

    return len(subgraphs)

if __name__ == '__main__':
    input = sys.stdin.read()
    data = list(map(int, input.split()))
    n, m = data[0:2]
    data = data[2:]
    edges = list(zip(data[0:(2 * m):2], data[1:(2 * m):2]))
    adj = [[] for _ in range(n)]
    for (a, b) in edges:
        adj[a - 1].append(b - 1)
        adj[b - 1].append(a - 1)
    print(number_of_components(adj))
