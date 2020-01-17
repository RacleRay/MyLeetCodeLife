# python3
from binarytree import BinaryTreeNode


# path要求遍历到叶子节点
path = []

def find_sum_path(root, target, cur_sum):
    cur_sum += root.data
    path.append(root.data)

    if root.leftChild is None \
      and root.rightChild is None \
      and cur_sum == target:
        for data in path:
            print(data, end=' ')

    if root.leftChild is not None:
        find_sum_path(root.leftChild, target, cur_sum)
    if root.rightChild is not None:
        find_sum_path(root.rightChild, target, cur_sum)

    # 清除已遍历并验证的路径结点
    cur_sum -= root.data
    path.remove(root.data)


def construct_tree():
    node4 = BinaryTreeNode(9)
    node3 = BinaryTreeNode(-1)
    node2 = BinaryTreeNode(-7)
    node1 = BinaryTreeNode(3, node3, node4)
    root = BinaryTreeNode(6, node1, node2)

    return root


if __name__ == '__main__':
    root = construct_tree()

    find_sum_path(root, 8, 0)

