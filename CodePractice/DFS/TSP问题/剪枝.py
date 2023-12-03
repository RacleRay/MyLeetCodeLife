class Result:
    def __init__(self):
        self.min_cost = float("inf")

class Solution:
    def minCost(self, n, roads):
        graph = self.construct_graph(roads, n)
        result = Result()
        self.dfs(1, n, [1], set([1]), 0, graph, result)
        return result.min_cost

    # 增加一个path判断当前遍历路径是否会被优化掉
    def dfs(self, city, n, path, visited, cost, graph, result):
        if len(visited) == n:
            result.min_cost = min(result.min_cost, cost)
            return

        for next_city in graph[city]:
            if next_city in visited:
                continue
            if self.has_better_path(graph, path, next_city):
                continue
            visited.add(next_city)
            path.append(next_city)
            self.dfs(next_city, n, visited, cost + graph[city][next_city], graph, result)
            path.pop(next_city)
            visited.remove(next_city)

    """
    这里两点：
    1. 只关注新加入 city 是否影响最优路径；
    2. 注意只对path进行了一次遍历，以为在每次加入一个新city时，对各种路径已经进行了最优性筛选
    """
    def has_better_path(self, graph, path, city):
        for i in range(1, len(path)):
            if graph[path[i]][path[i - 1]] + graph[path[-1]][city] > \
               graph[path[i]][city] + graph[path[-1]][path[i - 1]]:
                return True
        return False

    def construct_graph(self, roads, n):
        graph = {
            i: {j: float("inf") for j in range(1, n + 1)}
            for i in range(1, n + 1)
        }
        for a, b, c in roads:
            graph[a][b] = min(graph[a][b], c)
            graph[b][a] = min(graph[b][a], c)
        return graph