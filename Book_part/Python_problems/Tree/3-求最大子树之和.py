# python3
"""给定一颗二叉树，每个节点为正整数或者负整数，如何找到一颗子树，使得所有节点之和最大"""

from binarytree import BinaryTreeNode


max_sub_sum = -float('inf')
max_sub_tree_root = None

def find_max_sub_tree(root):
    """后序遍历思路求解"""
    if root is None:
        return 0

    left_sub_sum = find_max_sub_tree(root.leftChild)
    right_sub_sum = find_max_sub_tree(root.rightChild)
    current_sum = left_sub_sum + right_sub_sum + root.data

    global max_sub_sum
    global max_sub_tree_root
    if current_sum > max_sub_sum:
        max_sub_sum = current_sum
        max_sub_tree_root = root

    return current_sum


def construct_tree():
    node4 = BinaryTreeNode(9)
    node3 = BinaryTreeNode(-1)
    node2 = BinaryTreeNode(-7)
    node1 = BinaryTreeNode(3, node3, node4)
    root = BinaryTreeNode(6, node1, node2)

    return root


if __name__ == "__main__":
    root = construct_tree()

    find_max_sub_tree(root)
    print('Max sub sum:', max_sub_sum)
    print('Max sub node data:', max_sub_tree_root.data)











