class Result:
    def __init__(self):
        self.min_cost = float("inf")

class Solution:
    def minCost(self, n, roads):
        graph = self.construct_graph(roads, n)

        state_size = 1 << n
        f = [[float('inf')] * (n + 1) for _ in range(state_size)]
        f[1][1] = 0

        for state in range(state_size):
            for i in range(2, n + 1):
                if state & (1 << (i - 1)) == 0:
                    continue  # 倒数第i位为1继续下面逻辑
                prev_state = state ^ (1 << (i - 1)) #此时倒数第i位为1，变成了0
                for j in range(1, n + 1):
                    if prev_state & (1 << (i - 1)) == 0:
                        continue
                    # 状态转移，就是前一个state为1（path中），与当前state最优的cost的转移关系
                    f[state][i] = min(f[state][i], f[prev_state][j] + graph[j][i])
        return min(f[state_size - 1])

    def construct_graph(self, roads, n):
        graph = {
            i: {j: float("inf") for j in range(1, n + 1)}
            for i in range(1, n + 1)
        }
        for a, b, c in roads:
            graph[a][b] = min(graph[a][b], c)
            graph[b][a] = min(graph[b][a], c)
        return graph