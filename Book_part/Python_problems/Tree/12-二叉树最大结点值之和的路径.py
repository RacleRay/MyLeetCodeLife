from binarytree import BinaryTreeNode


def find_max_path_recursive(root):
    if root is None:
        return 0

    # 以root.leftChild为根结点的左子树的最大路径
    max_of_left = find_max_path_recursive(root.leftChild)
    max_of_right = find_max_path_recursive(root.rightChild)


    temp = root.data + max_of_left + max_of_right
    max_of_left_through_root = root.data + max_of_left
    max_of_right_through_root = root.data + max_of_right

    # 修改cur_max
    global cur_max
    tmp_cur_max = max([temp, max_of_left_through_root, max_of_right_through_root])
    if tmp_cur_max > cur_max:
        cur_max = tmp_cur_max

    # 需要返回max_of_left，max_of_right对应的左子树，右子树的最大值
    max_of_child = max_of_left if max_of_left > max_of_right else max_of_right

    return root.data + max_of_child

cur_max = -float('inf')

def find_max(root):
    global cur_max
    find_max_path_recursive(root)

    return cur_max


# 引用传递
# class Ref:
#     def __init__(self, data=None):
#         self.value = data


# cur_max = Ref(-float('inf'))
# # 注意不用global cur_max，而是在函数传参中传入cur_max
# find_max_path_recursive(root, cur_max)


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
    array = [2, 3, 5]
    root = array_to_tree(array)

    res = find_max(root)
    print(res)