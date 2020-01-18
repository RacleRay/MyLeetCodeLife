from binarytree import BinaryTreeNode


"""中间值：（最大值 + 最小值）/ 2"""
def get_min_node(root):
    if root is None:
        return None

    while root.leftChild is not None:
        root = root.leftChild

    return root


def get_max_node(root):
    if root is None:
        return None

    while root.rightChild is not None:
        root = root.rightChild

    return root


def get_avg_node(root):
    """第一个大于中间值avg的结点"""
    max_node = get_max_node(root)
    min_node = get_min_node(root)

    avg = (max_node.data + min_node.data) / 2
    res = None
    while root is not None:
        if root.data <= avg:
            root = root.rightChild
        else:
            res = root
            root = root.leftChild

    return res


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
    array = [i for i in range(1, 8)]
    root = array_to_tree(array)

    print(get_avg_node(root).data)