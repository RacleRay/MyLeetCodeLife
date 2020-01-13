# python3

from binarytree import BinaryTreeNode


class Solution:
    def __init__(self):
        self.pHead = None  # 双向链表头指针
        self.pEnd = None  # 双向链表尾指针

    def convert(self, root):
        """递归实现转换"""
        if root is None:
            return

        self.convert(root.leftChild)  # 中序遍历的顺序

        # 使用左右child成员变量指向链表的前后结点
        root.leftChild = self.pEnd  # 当前结点的前结点
        if self.pHead is None:  # 链表为空，确定头指针位置
            self.pHead = root
        else:
            self.pEnd.rightChild = root  # 当前结点成为pEnd的后继结点
        self.pEnd = root  # 移动尾指针

        self.convert(root.rightChild)

    @staticmethod
    def array_to_tree(array):
        """有序数组转化为二叉树"""
        if len(array) == 0:
            return None

        mid_index = len(array) // 2
        root = BinaryTreeNode(array[mid_index])

        # 递归
        root.leftChild = Solution.array_to_tree(array[: mid_index])
        root.rightChild = Solution.array_to_tree(array[mid_index + 1: ])

        return root


if __name__ == "__main__":
    array = [i for i in range(1, 8)]

    root = Solution.array_to_tree(array)

    solution = Solution()
    solution.convert(root)

    print('正向遍历：')
    cur = solution.pHead
    while cur != None:
        print(cur.data, end='')
        cur = cur.rightChild

    print('\n' + '后向遍历：')
    cur = solution.pEnd
    while cur != None:
        print(cur.data, end='')
        cur = cur.leftChild