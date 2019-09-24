# python3

import sys
import threading


class Node:
    def __init__(self, data):
        self.data = data
        self.childs = []


def compute_height_naive(n, parents):
    # Replace this code with a faster implementation
    max_height = 0
    for vertex in range(n):
        height = 0
        current = vertex
        while current != -1:
            height += 1
            current = parents[current]
        max_height = max(max_height, height)
    return max_height


def compute_height(n, parents):
        # a faster implementation
        if n == 0:
            return 0

        nodes = []
        for i in range(n):
            nodes.append(Node(i))

        # build an arbitrary tree
        for i in range(n):
            parents_index = parents[i]
            if parents_index == -1:
                root_index = i
            else:
                nodes[parents_index].childs.append(nodes[i])

        def _compute_height(node):

            if node.childs == []:
                return 1

            max_height = 0
            for child in node.childs:
                max_height = max(_compute_height(child), max_height)

            return max_height + 1

        return _compute_height(nodes[root_index])


def main():
    n = int(input())
    parents = list(map(int, input().split()))
    print(compute_height(n, parents))


# In Python, the default limit on recursion depth is rather low,
# so raise it here for this problem. Note that to take advantage
# of bigger stack, we have to launch the computation in a new thread.
sys.setrecursionlimit(10**7)  # max depth of recursion
threading.stack_size(2**27)   # new thread will get stack of such size
threading.Thread(target=main).start()
