# python3
from binarytree import BinaryTreeNode


def copy_tree(root):
    if root is None:
        return None

    copy_node = BinaryTreeNode(root.data)
    copy_node.leftChild = copy_tree(root.leftChild)
    copy_node.rightChild = copy_tree(root.rightChild)

    return copy_node


def mid_order_retrieve(root):
    """中序遍历"""
    if root is None:
        return

    mid_order_retrieve(root.leftChild)
    print(root.data, end=' ')
    mid_order_retrieve(root.rightChild)


def array_to_tree(array):
    if len(array) == 0:
        return None

    mid_index = len(array) // 2
    root = BinaryTreeNode(array[mid_index])

    # 递归
    root.leftChild = array_to_tree(array[: mid_index])
    root.rightChild = array_to_tree(array[mid_index + 1: ])

    return root


if __name__ == '__main__':
    array = [1, 3, 2, 5, 7, 6, 4]
    root = array_to_tree(array)

    mid_order_retrieve(root)
    print()
    mid_order_retrieve(copy_tree(root))