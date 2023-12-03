#/*************************************************************************
#    > File Name: AnyTopological.py
#    > Author: racle
#    > Mail: racleray@qq.com
#    > Created Time: 
# ************************************************************************/
# coding=utf-8

#https://www.lintcode.com/problem/127/
from dataclasses import dataclass
from typing import Generic, List, TypeVar
from collections import deque

T = TypeVar('T')


@dataclass
class Node:
    label: int
    neighbors: List[Node]

class Solution:
    def topSort(self, graph):
        # 1. indegree
        node_to_indegree = self.get_indegree(graph)

        # 2. 0 indegree  =>  in queue
        start_node = [n for n in graph if node_to_indegree[n] == 0]
        queue = deque(start_node)

        # 3. pop queue and remove indegree, find 0 indegree node
        ordered = []
        while queue:
            node = queue.popleft()
            ordered.append(node)
            for neighbor in node.neighbors:
                node_to_indegree[neighbor] -= 1
                if node_to_indegree[neighbor] == 0:
                    queue.append(neighbor)

        #def gen():
            #while queue:
                #node = queue.popleft()
                #ordered.append(node)
                #for neighbor in node.neighbors:
                    #node_to_indegree[neighbor] -= 1
                    #if node_to_indegree[neighbor] == 0:
                        #yield neighbor

        #ordered2 = [x for x in gen()]

        return ordered

        
    def get_indegree(self, graph):
        node_to_indegree = {x: 0 for x in graph}
        for node in graph:
            for neighbor in node.neighbors:
                node_to_indegree[neighbor] += 1

        return node_to_indegree
