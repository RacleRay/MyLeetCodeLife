# python3


# class Edge:
#
#     def __init__(self, u, v, capacity):
#         self.u = u
#         self.v = v
#         self.capacity = capacity
#         self.flow = 0
#
# # This class implements a bit unusual scheme for storing edges of the graph,
# # in order to retrieve the backward edge for a given edge quickly.
# class FlowGraph:
#     """forward edges: graph中为偶数index的edge；backward edges: graph中为奇数index的edge
#     graph：一个列表代表一个节点，列表存储edge的index
#     """
#     def __init__(self, n):
#         # List of all - forward and backward - edges
#         self.edges = []
#         # These adjacency lists store only indices of edges in the edges list
#         self.graph = [[] for _ in range(n)]
#
#     def add_edge(self, from_, to, capacity):
#         # Note that we first append a forward edge and then a backward edge,
#         # so all forward edges are stored at even indices (starting from 0),
#         # whereas backward edges are stored at odd indices.
#         forward_edge = Edge(from_, to, capacity)
#         backward_edge = Edge(to, from_, 0)
#         self.graph[from_].append(len(self.edges))
#         self.edges.append(forward_edge)
#         self.graph[to].append(len(self.edges))
#         self.edges.append(backward_edge)
#
#     def size(self):
#         return len(self.graph)
#
#     def get_ids(self, from_):
#         return self.graph[from_]
#
#     def get_edge(self, id):
#         return self.edges[id]
#
#     def add_flow(self, id, flow):
#         # To get a backward edge for a true forward edge (i.e id is even), we should get id + 1
#         # due to the described above scheme. On the other hand, when we have to get a "backward"
#         # edge for a backward edge (i.e. get a forward edge for backward - id is odd), id - 1
#         # should be taken.
#         #
#         # It turns out that id ^ 1 works for both cases. Think this through!
#         self.edges[id].flow += flow
#         self.edges[id ^ 1].flow -= flow


def read_data():
    vertex_count, edge_count = map(int, input().split())
    graph = [[0 for _ in range(vertex_count)] for _ in range(vertex_count)]

    for _ in range(edge_count):
        u, v, capacity = map(int, input().split())
        if graph[u - 1][v - 1] == 0:
            graph[u - 1][v - 1] = capacity
        else:
            graph[u - 1][v - 1] += capacity

    return graph


def BFS(graph, s, t, parent):
    # Return True if there is node that has not iterated.
    visited = [False] * len(graph)
    queue = []
    queue.append(s)
    visited[s] = True

    while queue:
        u = queue.pop(0)
        for ind in range(len(graph[u])):
            if visited[ind] == False and graph[u][ind] > 0:
                queue.append(ind)
                visited[ind] = True
                parent[ind] = u

    return True if visited[t] else False


def max_flow(graph, source, sink):
    # This array is filled by BFS and to store path
    parent = [-1] * (len(graph))
    max_flow = 0
    while BFS(graph, source, sink, parent):
        path_flow = float("Inf")
        s = sink

        while s != source:
            # Find the minimum value in select path
            path_flow = min(path_flow, graph[parent[s]][s])
            s = parent[s]

        max_flow += path_flow
        v = sink

        while v != source:
            u = parent[v]
            graph[u][v] -= path_flow
            graph[v][u] += path_flow
            v = parent[v]

    return max_flow


if __name__ == '__main__':
    graph = read_data()
    print(max_flow(graph, 0, len(graph) - 1))


# 5 7
# 1 2 2
# 2 5 5
# 1 3 6
# 3 4 2
# 4 5 1
# 3 2 3
# 2 4 1

# 4 5
# 1 2 10000
# 1 3 10000
# 2 3 1
# 3 4 10000
# 2 4 10000

# 2 5
# 1 1 10000
# 1 2 1
# 1 2 4
# 1 2 100
# 2 1 900