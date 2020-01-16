# python3
from binarytree import BinaryTreeNode


def find_path_from_root(root, node, path):
    """方法一，从根节点开始找到路径，进行对比。先找到root到目标node的路径。
    path -- list.
    """
    if root is None:
        return False

    if root == node:
        path.insert(0, root)
        return True

    if find_path_from_root(root.leftChild, node, path) or \
      find_path_from_root(root.rightChild, node, path):
        path.insert(0, root)
        return True

    return False


def find_parent_node(root, node1, node2):
    path_1 = []
    path_2 = []

    find_path_from_root(root, node1, path_1)
    find_path_from_root(root, node2, path_2)

    co_parent = None
    idx = 0
    shorter_len = min(len(path_1), len(path_2))
    while idx < shorter_len:
        if path_1[idx].data == path_2[idx].data:
            co_parent = path_1[idx]
        else:
            break
        idx += 1

    return co_parent


############# 方法二 ###############
import math


def get_number(root, node, num):
    """找到node在二叉树中的编号（按完全二叉树，从左到右顺序）
    num -- root结点编号
    """
    if root is None:
        return False

    if root == node:
        return True

    nonlocal num
    num *= 2
    # node在左子树中
    if get_number(root.leftChild, node, num):
        return True
    else:
        num += 1
        return get_number(root.rightChild, node, num)


def get_node(root, num):
    """根据结点编号找出相应结点"""
    if root is None or num < 0:
        return None

    if num == 1:
        return root

    # 结点编号对应的二进制位数
    lens = math.log(num) // math.log(2)

    # 去掉最左边的1，剩下的数字，每个0代表左孩子，1代表右孩子
    num -= 1 << lens
    while lens > 0:
        # 判断num的当前（lens - 1）位是否为1
        if (1 << (lens - 1) & num) == 1:
            root = root.rightChild
        else:
            root = root.leftChild
        lens -= 1

    return root


def find_parent_node_2(root, node1, node2):
    num_1 = 1
    num_2 = 1

    get_number(root, node1, num_1)
    get_number(root, node2, num_2)

    while num_1 != num_2:
        if num_1 > num_2:
            num_1 //= 2
        else:
            num_2 //= 2

    return get_node(root, num_1)


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
    array = [i for i in range(1, 11)]
    root = array_to_tree(array)

    node1 = root.leftChild.leftChild.leftChild
    node2 = root.leftChild.rightChild

    co_parent = find_parent_node_2(root, node1, node2)

    if co_parent:
        print(co_parent.data)