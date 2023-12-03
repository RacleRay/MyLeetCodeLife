from __future__ import annotations
from dataclasses import dataclass


# !/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@File    :   二叉搜索树.py
@Author  :   Racle
@Version :   1.0
@Desc    :   None
'''


@dataclass
class Node:
    val: int = 0
    left: Node = None
    right: Node = None


class Solution:
    def search_bst(self, root, val):
        if not root:
            return None
        if val < root.val:
            return self.search_bst(root.left, val)
        elif val > root.val:
            return self.search_bst(root.right, val)
        else:
            return root

    def update_bst(self, root, target, val):
        if not root:
            return None
        if target < root.val:
            self.update_bst(root.left, target, val)
        elif target > root.val:
            self.update_bst(root.right, target, val)
        else:
            root.val = val

    def insert(self, root, node):
        if not root:
            return node
        if root.val > node.val:
            root.left = self.insert(root.left, node)
        else:
            root.right = self.insert(root.right, node)
        return root  # 回溯

    def remove(self, root, val):
        dummy = Node()
        dummy.left = root

        parent = self._find_parent(dummy, root, val)
        node = None

        if parent.left and parent.left.val == val:
            node = parent.left
        elif parent.right and parent.right.val == val:
            node = parent.right
        else:  # not found
            return dummy.left

        self._delete_node(parent, node)
        return dummy.left

    def _find_parent(self, parent, node, val):
        if not node:
            return parent
        if node.val == val:
            return parent
        if val < node.val:
            return self._find_parent(node, node.left, val)
        else:
            return self._find_parent(node, node.right, val)

    @staticmethod
    def _delete_node(parent, node):
        if not node.right:  # 不需要从右子树提取新的父节点
            if parent.left == node:
                parent.left = node.left
            else:
                parent.right = node.left
        else:
            # 找到刚好比 node 大的下一个节点作为新的 node
            curr = node.right
            prev = node
            while curr.left:
                prev = curr
                curr = curr.left

            # 处理取出 curr 后，子树的结构
            # curr存在左子树
            if prev.left == curr:
                prev.left = curr.right  # curr 从树中脱离
            else:  # curr 只有右子树
                prev.right = curr.right

            # curr 继承 node 的左右子树
            curr.left = node.left
            curr.right = node.right

            # 当前 curr 是顶替 node 的存在
            # node 为左子树
            if parent.left == node:
                parent.left = curr
            else:  # node 为右子树
                parent.right = curr


if __name__ == "__main__":
    solution = Solution()
