# python3
from itertools import permutations
INF = 10 ** 9


class Graph:
    def __init__(self, graph):
        self.graph = graph
        self.best_weight = INF
        self.best_path = []


def read_data():
    n, m = map(int, input().split())
    graph = [[INF] * n for _ in range(n)]
    for _ in range(m):
        u, v, weight = map(int, input().split())
        u -= 1
        v -= 1
        graph[u][v] = graph[v][u] = weight
    return Graph(graph)


def print_answer(path_weight, path):
    print(path_weight)
    if path_weight == -1:
        return
    print(' '.join(map(str, path)))


def optimal_path(graph):
    # This solution tries all the possible sequences of stops.
    # It is too slow to pass the problem.
    # Implement a more efficient algorithm here.
    find_optimal_path(graph, 0, 0, set(), 0, [])

    if graph.best_weight == INF:
        return (-1, [])
    return (graph.best_weight, [x + 1 for x in graph.best_path])


def find_optimal_path(graph, from_vertex, to_vertex, explored, cur_weight, cur_path):

    if from_vertex != to_vertex:
        cur_weight += graph.graph[from_vertex][to_vertex]

    explored.add(to_vertex)
    cur_path.append(to_vertex)

    # if the rest of the graph has been explored and a path exists to the initial vertex,
    # compute the rest
    if len(explored) == len(graph.graph) and graph.graph[to_vertex][0] != INF:
        cur_weight += graph.graph[to_vertex][0]
        if cur_weight < graph.best_weight:
            graph.best_weight = cur_weight
            graph.best_path = cur_path
            return

    # prune the branch if it already exceeds the current best solution
    if cur_weight > graph.best_weight:
        return

    # otherwise explore all unexplored vertices; keep the vertex positions for bookkeeping
    weights_list = [i for i in range(len(graph.graph)) if i not in explored]
    for unexplored_vertex in weights_list:
        find_optimal_path(graph,
                          to_vertex,
                          unexplored_vertex,
                          explored.copy(),
                          cur_weight,
                          cur_path[:])


# 4 6
# 1 2 20
# 1 3 42
# 1 4 35
# 2 3 30
# 2 4 34
# 3 4 12

# 4 4
# 1 2 1
# 2 3 4
# 3 4 5
# 4 2 1

if __name__ == '__main__':
    print_answer(*optimal_path(read_data()))
