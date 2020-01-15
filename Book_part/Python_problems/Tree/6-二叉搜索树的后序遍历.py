# python3
from binarytree import BinaryTreeNode


"""判断一个数组是否是二叉搜索树的后序遍历序列。"""

def is_after_order_array(array):
    if array is None:
        return False

    length = len(array)
    # 数组的最后一个节点必定是根结点（假如是后序遍历结果）
    root_data = array[length - 1]

    # 自左向右找到第一个大于root_data的值，应为root左孩子的数值
    i = 0
    while i < length - 1:
        if array[i] > root_data:
            break
        i += 1

    # 从i结点之后的data应该大于root_data
    j = i
    while j < length - 1:
        if array[j] < root_data:
            return False
        j += 1

    left_tree = True
    right_tree = True
    # 递归检测子树
    if i > 0:
        left_tree = is_after_order_array(array[: i])
    if j < length - 1:
        right_tree = is_after_order_array(array[i: ])

    return left_tree and right_tree



if __name__ == "__main__":
    array = [1, 3, 2, 5, 7, 6, 4]
    result = is_after_order_array(array)

    print(result)