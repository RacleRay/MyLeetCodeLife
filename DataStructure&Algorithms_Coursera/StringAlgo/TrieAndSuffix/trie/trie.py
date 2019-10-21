#Uses python3
import sys

# Return the trie built from patterns
# in the form of a dictionary of dictionaries,
# e.g. {0:{'A':1,'T':2},1:{'C':3}}
# where the key of the external dictionary is
# the node ID (integer), and the internal dictionary
# contains all the trie edges outgoing from the corresponding
# node, and the keys are the letters on those edges, and the
# values are the node IDs to which these edges lead.
def build_trie(patterns):
    tree = dict()
    tree[0] = {}
    total_node_index = 0
    for pattern in patterns:
        currentNode = 0
        for i in range(len(pattern)):
            currentSymbol = pattern[i]

            # currentSymbol在子节点中
            if tree.get(currentNode) != None and currentSymbol in tree.get(currentNode):
                currentNode = tree.get(currentNode)[currentSymbol]
            else:
                total_node_index += 1
                if tree.get(currentNode) == None: # new node
                        tree[currentNode] = {}
                tree[currentNode][currentSymbol] = total_node_index  # new edge
                currentNode = total_node_index

    return tree


if __name__ == '__main__':
    # 1 ATA
    # 3 AT AG AC
    # 3 ATAGA ATC GAT
    patterns = sys.stdin.read().split()[1:]
    tree = build_trie(patterns)
    for node in tree:
        for c in tree[node]:
            print("{}->{}:{}".format(node, tree[node][c], c))
