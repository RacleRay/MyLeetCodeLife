# python3
class MaxMatching:
    def read_data(self):
        self.n, self.m = map(int, input().split())
        adj_matrix = [list(map(int, input().split())) for i in range(self.n)]
        return adj_matrix

    def write_response(self, matching):
        res = [str(-1)] * self.n
        for from_, to in matching:
            res[from_ - 1] = str(to - self.n)
        print(' '.join(res))
        # line = [str(-1 if x == -1 else x + 1) for x in matching]
        # print(' '.join(line))

    @staticmethod
    def BFS(graph, s, t, parent):
        # Return True if there is node that has not iterated.
        visited = [False] * len(graph)
        queue = [s]
        visited[s] = True

        while queue:
            u = queue.pop(0)
            for ind in range(len(graph[u])):
                if visited[ind] == False and graph[u][ind] > 0:
                    queue.append(ind)
                    visited[ind] = True
                    parent[ind] = u

        return True if visited[t] else False

    def find_matching(self, adj_matrix):
        # Replace this code with an algorithm that finds the maximum
        # matching correctly in all cases.
        size = self.n + self.m + 2
        graph = [[0 for _ in range(size)] for _ in range(size)]
        for x in range(self.n):
            for y in range(self.m):
                graph[x + 1][self.n + y + 1] = adj_matrix[x][y]
        for i in range(self.n):
            graph[0][i + 1] = 1
        for j in range(self.m):
            graph[self.n + j + 1][-1] = 1

        source = 0
        sink = size - 1

        parent = [-1] * (len(graph))
        max_flow = 0
        res = []
        temp = [i[:] for i in graph]

        while self.BFS(graph, source, sink, parent):
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

        for i in range(1, self.n + 1):
            for j in range(self.n + 1, self.n + self.m + 1):
                if graph[i][j] == 0 and temp[i][j] > 0:
                    res.append((i, j))

        return res


    def solve(self):
        adj_matrix = self.read_data()
        matching = self.find_matching(adj_matrix)
        self.write_response(matching)

if __name__ == '__main__':
    max_matching = MaxMatching()
    max_matching.solve()


# 3 4
# 1 1 0 1
# 0 1 0 0
# 0 0 0 0

# 2 2
# 1 1
# 1 0