#/*************************************************************************
#    > File Name: UniqueOrder.py
#    > Author: racle
#    > Mail: racleray@qq.com
#    > Created Time: 
# ************************************************************************/
# coding=utf-8


#https://www.lintcode.com/problem/605/

from typing import (
    List,
)
import collections

class Solution:
    """
    @param org: a permutation of the integers from 1 to n
    @param seqs: a list of sequences
    @return: true if it can be reconstructed only one or false
    """
    def sequence_reconstruction(self, org: List[int], seqs: List[List[int]]) -> bool:
        # 1. build graph
        graph = self._build_graph(seqs)

        # 2. topological sort
        topo_res = self.topological_sort(graph)

        return topo_res == org

    @staticmethod
    def _build_graph(seqs):
        graph = {}
        for seq in seqs:
            for node in seq:
                if node not in graph:
                    graph[node] = set()

        for seq in seqs:
            for i in range(1, len(seq)):
                graph[seq[i - 1]].add(seq[i])

        return graph

    def _get_indegrees(self, graph):
        indegrees = {node: 0 for node in graph}
        for node in graph:
            for neighbor in graph[node]:
                indegrees[neighbor] += 1

        return indegrees

    def topological_sort(self, graph):
        indegrees = self._get_indegrees(graph)

        queue = collections.deque()
        for node in graph:
            if indegrees[node] == 0:
                queue.append(node)

        order = []
        while queue:
            if len(queue) > 1: return None
            node = queue.popleft()
            order.append(node)
            for neighbor in graph[node]:
                indegrees[neighbor] -= 1
                if indegrees[neighbor] == 0:
                    queue.append(neighbor)

        if len(order) == len(indegrees): return order

        return None

