from heapq import heapify, heappop, heappush
from typing import (
    List,
)


class Solution:
    """
    @param words: a list of words
    @return: a string which is correct order
    """

    def alien_order(self, words: List[str]) -> str:
        # build graph
        graph = self.build_graph(words)

        # topological sort
        res = self.topological_sort(graph)

        return res

    def build_graph(self, words):
        graph = {}

        for word in words:
            for c in word:
                if c not in graph:
                    graph[c] = set()

        n = len(words)
        for i in range(n - 1):
            for j in range(min(len(words[i]), len(words[i + 1]))):
                if words[i][j] != words[i + 1][j]:
                    graph[words[i][j]].add(words[i + 1][j])
                    break
                if j == min(len(words[i]), len(words[i + 1])) - 1:
                    if len(words[i]) > len(words[i + 1]):
                        return None

        return graph

    def topological_sort(self, graph):
        indegree = self.get_indegree(graph)

        queue = [node for node in graph if indegree[node] == 0]

        # 最小字典序
        heapify(queue)
        order = ""

        while queue:
            node = heappop(queue)
            order += node
            for neighbor in graph[node]:
                indegree[neighbor] -= 1
                if indegree[neighbor] == 0:
                    heappush(queue, neighbor)

        return order if len(order) == len(graph) else ""

    def get_indegree(self, graph):
        indegree = {node: 0 for node in graph}
        for node in graph:
            for neighbor in graph[node]:
                indegree[neighbor] += 1
        return indegree


if __name__ == "__main__":
    s = Solution()
    words = ["wrt", "wrf", "er", "ett", "rftt"]
    print(s.alien_order(words))
