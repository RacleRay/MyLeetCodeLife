# python3
"""相同的结构，相同的参数"""

from binarytree import BinaryTreeNode


def is_equal(root_a, root_b):
    if root_a == root_b == None:
        return True

    if (root_a or root_b) and (not root_a or not root_b):
        return False

    if root_a.data == root_b.data:
        return is_equal(root_a.leftChild, root_b.leftChild) and \
               is_equal(root_a.rightChild, root_b.rightChild)
    else:
        return False


def construct_tree():
    node4 = BinaryTreeNode(9)
    node3 = BinaryTreeNode(-1)
    node2 = BinaryTreeNode(-7)
    node1 = BinaryTreeNode(3, node3, node4)
    root = BinaryTreeNode(6, node1, node2)

    return root


if __name__ == "__main__":
    root_a = construct_tree()
    root_b = construct_tree()

    print("Result: ", is_equal(root_a, root_b))
