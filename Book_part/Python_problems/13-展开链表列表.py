# python3

class Node:
    def __init__(self, data):
        self.data = data
        self.right = None  # 横向链表
        self.down = None   # 纵向链表


class MergeList:
    def __init__(self):
        self.head = None

    def merge(self, l1, l2):
        """使用归并排序思路，合并两个纵向链表"""
        if l1 is None:
            return l2

        if l2 is None:
            return l1

        if l1.data < l2.data:  # 取小
            result_list = l1
            result_list.down = self.merge(l1.down, l2)
        else:
            result_list = l2
            result_list.down = self.merge(l1, l2.down)

        return result_list

    def flatten(self, root):
        if root is None or root.right is None:
            return root

        root.right = self.flatten(root.right)

        # 从最后到头节点，依次合并两个链表
        root = self.merge(root, root.right)

        return root

    def insert(self, head_ref, data):
        """插入数据到链表"""
        new_node = Node(data)
        new_node.down = head_ref
        head_ref = new_node

        return head_ref

    def print_list(self):
        tmp = self.head

        while tmp != None:
            print(tmp.data, end=' ')
            tmp = tmp.down

        print('\n')


if __name__ == '__main__':
    L = MergeList()

    L.head = L.insert(L.head, 31)
    L.head = L.insert(L.head, 8)
    L.head = L.insert(L.head, 6)
    L.head = L.insert(L.head, 3)

    L.head.right = L.insert(L.head.right, 21)
    L.head.right = L.insert(L.head.right, 11)

    L.head.right.right = L.insert(L.head.right.right, 50)
    L.head.right.right = L.insert(L.head.right.right, 22)
    L.head.right.right = L.insert(L.head.right.right, 15)

    L.head.right.right.right = L.insert(L.head.right.right.right, 55)
    L.head.right.right.right = L.insert(L.head.right.right.right, 40)
    L.head.right.right.right = L.insert(L.head.right.right.right, 39)
    L.head.right.right.right = L.insert(L.head.right.right.right, 30)

    L.head = L.flatten(L.head)

    L.print_list()

