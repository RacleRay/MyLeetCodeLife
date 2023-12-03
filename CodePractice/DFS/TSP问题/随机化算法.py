class Result:
    def __init__(self):
        self.min_cost = float("inf")

RANDOM_TIMES = 10000 # 测试得到合适的值

class Solution:
    def minCost(self, n, roads):
        graph = self.construct_graph(roads, n)

        min_cost = float('inf')
        for _ in range(RANDOM_TIMES):
            # 遗传算法
            path = self.get_random_path(n)
            cost = self.adjust_path(path, graph)
            min_cost = min(min_cost, cost)
        return min_cost

    def construct_graph(self, roads, n):
        graph = {
            i: {j: float("inf") for j in range(1, n + 1)}
            for i in range(1, n + 1)
        }
        for a, b, c in roads:
            graph[a][b] = min(graph[a][b], c)
            graph[b][a] = min(graph[b][a], c)
        return graph

    def get_random_path(self, n):
        import random

        path = [i for i in range(1, n + 1)]
        for i in range(2, n):
            j = random.randint(1, i)
            path[i], path[j] = path[j], path[i]

        return path

    def adjust_path(self, path, graph):
        n = len(graph)
        adjusted = True
        while adjusted:
            adjusted = False
            for i in range(1, n):
                for j in range(i + 1, n):
                    # 交换策略
                    if self.can_swap(path, i, j, graph):
                        path[i], path[j] = path[j], path[i]
                        adjusted = True

                    # 反转策略
                    # if self.can_reverse(path, i, j, graph):
                    #     self.reverse(path, i, j)
                    #     adjusted = True
        cost = 0
        for i in range(1, n):
            cost += graph[path[i - 1]][path[i]]
        return cost

    def can_swap(self, path, i, j, graph):
        # 交换两个city位置，变异更好的path
        before = self.adjcent_cost(path, i, path[i], graph)
        before += self.adjcent_cost(path, j, path[j], graph)
        after = self.adjcent_cost(path, i, path[i], graph)
        after += self.adjcent_cost(path, j, path[j], graph)
        return before > after

    def adjcent_cost(self, path, i, city, graph):
        # city前后两条path的cost
        cost = graph[path[i - 1]][city]
        if i + 1 < len(path):
            cost += graph[city][path[i + 1]]
        return cost

    # 第二种策略：反转i和j的位置
    def can_reverse(self, path, i, j, graph):
        before = graph[path[i - 1]][path[i]]
        if j + 1 < len(path):
            before += graph[path[j]][path[j + 1]]
        after = graph[path[i - 1]][path[j]]
        if j + 1 < len(path):
            after += graph[path[i]][path[j + 1]]
        return before > after

    def reverse(self, path, i, j):
        while i < j:
            path[i], path[j] = path[j], path[i]
            i += 1
            j -= 1