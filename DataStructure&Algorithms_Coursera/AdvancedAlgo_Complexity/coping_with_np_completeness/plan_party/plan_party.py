#uses python3

import sys
import threading

# This code is used to avoid stack overflow issues
sys.setrecursionlimit(10**6) # max depth of recursion
threading.stack_size(2**26)  # new thread will get stack of such size


class Vertex:
    def __init__(self, weight):
        self.weight = weight
        self.children = []
        self.maxweight = None


def ReadTree():
    size = int(input())
    tree = [Vertex(w) for w in map(int, input().split())]
    for i in range(1, size):
        a, b = list(map(int, input().split()))
        tree[a - 1].children.append(b - 1)
        tree[b - 1].children.append(a - 1)
    return tree


def dfs(tree, vertex, parent):
    # This is a template function for processing a tree using depth-first search.
    # Write your code here.
    # You may need to add more parameters to this function for child processing.
    if tree[vertex].maxweight == None:

        if  not tree[vertex].children or (tree[vertex].children[0] == parent
                                          and len(tree[vertex].children) == 1):
            tree[vertex].maxweight = tree[vertex].weight
        else:
            weight_skip = tree[vertex].weight

            for child in tree[vertex].children:
                if child != parent:

                    for gchild in tree[child].children:
                        if gchild != child and gchild != parent and gchild != vertex:
                            weight_skip += dfs(tree, gchild, child)

            weight_direct = 0
            for child in tree[vertex].children:
                if child != parent:
                    weight_direct += dfs(tree, child, vertex)

            tree[vertex].maxweight = max(weight_skip, weight_direct)

    return tree[vertex].maxweight


def MaxWeightIndependentTreeSubset(tree):
    size = len(tree)

    if size == 0:
        return 0
    maxweight = dfs(tree, 0, -1)

    return maxweight


def main():
    tree = ReadTree();
    weight = MaxWeightIndependentTreeSubset(tree);
    print(weight)


# 5
# 1 5 3 7 5
# 5 4
# 2 3
# 4 2
# 1 2


# This is to avoid stack overflow issues
threading.Thread(target=main).start()
