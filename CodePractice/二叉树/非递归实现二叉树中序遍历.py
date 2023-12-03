"""

"""


def hasNext(stack):
    return len(stack) > 0


def next_(stack):
    """
    中序遍历：先左子树，再当前节点，后右子树
    """
    node = stack[-1]
    if node.right is not None:  # next遍历时，对于没有遇到过的右孩子，找其子树的最左结点
        n = node.right
        while n is not None:
            stack.append(n)
            n = n.left
    else:  # 没有右孩子时，开始pop输出next
        n = stack.pop()
        # 当当前结点的右孩子是已经被 pop 过的结点时，继续pop。不影响第一个if的逻辑
        while stack and stack[-1].right == n:
            n = stack.pop()

    return node


def traversal(root):
    """
    中序遍历：
        先左子树，再当前节点，后右子树
    """
    stack = []
    res = []
    # left unitl None
    while root is not None:
        stack.append(root)
        root = root.left

    # output
    while hasNext(stack):
        res.append(next_(stack))

    return res


"""
method 2

相比第一种，效率高一些，只要是next_遍历到的结点都被pop

但是第一种方式，如果将left和right互换，那么就可以得到中序遍历的前继结点。
这是第二种方式做不到的。
"""


class BSTIterator:
    def __init__(self, root):
        self.stack = []
        self.find_most_left(root)

    def find_most_left(self, node):
        while node:
            self.stack.append(node)
            node = node.left

    def has_next(self):
        return bool(self.stack)

    def next_(self):
        node = self.stack.pop()
        if node.right:
            self.find_most_left(node.right)
        return node
