
# https://www.lintcode.com/problem/616/
import collections

class Solution:
    """
    @param: numCourses: a total of n courses
    @param: prerequisites: a list of prerequisite pairs
    @return: the course order
    """
    def findOrder(self, numCourses, prerequisites):
        graph = [[] for i in range(numCourses)]

        in_degree = [0] * numCourses
        for node, node_pre in prerequisites:
            graph[node_pre].append(node)
            in_degree[node]+=1

        queue = collections.deque()
        for i in range(numCourses):
            if in_degree[i] == 0:
                queue.append(i)

        n_chosen = 0
        order = []
        while queue:
            check = queue.popleft()
            order.append(check)
            n_chosen += 1
            for next_pos in graph[check]:
                in_degree[next_pos] -= 1
                if in_degree[next_pos] == 0:
                    queue.append(next_pos)

        return order if n_chosen == numCourses else []
