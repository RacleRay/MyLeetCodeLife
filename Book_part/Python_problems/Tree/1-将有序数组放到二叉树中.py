# python3
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


def mid_order_retrieve(root):
    """中序遍历"""
    if root is None:
        return

    mid_order_retrieve(root.leftChild)
    print(root.data, end=' ')
    mid_order_retrieve(root.rightChild)


if __name__ == '__main__':
    array = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]
    print(array)

    root = array_to_tree(array)
    mid_order_retrieve(root)
