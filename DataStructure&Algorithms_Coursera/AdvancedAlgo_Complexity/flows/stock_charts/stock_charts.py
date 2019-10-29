# python3
class StockCharts:
    """图构建方式有问题，还未修改，有时间再改"""

    def read_data(self):
        self.n, self.m = map(int, input().split())
        stock_data = [list(map(int, input().split())) for i in range(self.n)]
        return stock_data

    def write_response(self, result):
        print(result)

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

    def min_charts(self, stock_data):
        # Replace this incorrect greedy algorithm with an
        # algorithm that correctly finds the minimum number
        # of charts on which we can put all the stock data
        # without intersections of graphs on one chart.
        size = self.n + self.m
        graph = [[0 for _ in range(size)] for _ in range(size)]
        for x in range(self.n):
            for y in range(self.m):
                graph[x][self.n + y] = stock_data[x][y]
        # for i in range(self.n):
        #     graph[0][i + 1] = 1
        # for j in range(self.m):
        #     graph[self.n + j + 1][-1] = 1

        source = 0
        sink = size - 1

        parent = [-1] * (len(graph))
        max_flow = 0

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

        return max_flow


    def solve(self):
        stock_data = self.read_data()
        result = self.min_charts(stock_data)
        self.write_response(result)

if __name__ == '__main__':
    stock_charts = StockCharts()
    stock_charts.solve()

# 3 4
# 1 2 3 4
# 2 3 4 6
# 6 5 4 3