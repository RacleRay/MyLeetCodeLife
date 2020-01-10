# python3
from collections import deque

from binarytree import BinaryTreeNode


def array_to_tree(array):
    if len(array) == 0:
        return None

    mid_index = len(array) // 2
    root = BinaryTreeNode(array[mid_index])

    # 递归
    root.leftChild = array_to_tree(array[: mid_index])
    root.rightChild = array_to_tree(array[mid_index + 1: ])

    return root


def layer_order_retrieve(root):
    """层序遍历"""
    if root is None:
        return

    queue = deque()
    queue.append(root)

    while len(queue) > 0:
        current_node = queue.popleft()
        print(current_node.data, end=' ')

        if current_node.leftChild != None:
            queue.append(current_node.leftChild)
        if current_node.rightChild != None:
            queue.append(current_node.rightChild)


if __name__ == '__main__':
    array = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
    root = array_to_tree(array)

    print("Result: ")
    layer_order_retrieve(root)