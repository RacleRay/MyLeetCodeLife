from __future__ import annotations

#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@File    :   Morris算法.py
@Author  :   Racle
@Version :   1.0
@Desc    :   None
'''

"""
与递归和使用栈空间遍历的思想不同，Morris 算法使用二叉树中的叶节点的right指针
来保存后面将要访问的节点的信息，当这个right指针使用完成之后，再将它置为null，

但是在访问过程中有些节点会访问两次，所以与递归的空间换时间的思路不同，
Morris则是使用时间换空间的思想。
"""

from dataclasses import dataclass

@dataclass
class Node:
    val: int = 0
    left: Node = None
    right: Node = None

class Solution:
    def inorder(self, root: Node):
        """
        节点的right指针保存后面将要访问的节点的信息

        1. 如果当前节点的左孩子为空，则输出当前节点并将其右孩子作为当前节点。
        2. 如果当前节点的左孩子不为空，在当前节点的左子树中找到当前节点在中序遍历下的前驱节点。
             如果前驱节点的右孩子为空，将它的右孩子设置为当前节点。当前节点更新为当前节点的左孩子。
             如果前驱节点的右孩子为当前节点，将它的右孩子重新设为空（恢复树的形状）。输出当前节点。当前节点更新为当前节点的右孩子。
        3. 重复1、2两步直到当前节点为空。
        """
        nums = []
        curr = None
        while root:
            if root.left:
                curr = root.left
                while curr.right and curr.right != root:
                    curr = curr.right

                if curr.right == root: # 叶子节点right指针，不用回溯，直接到遍历位置
                    nums.append(root.val)
                    curr.right = None
                    root = root.right
                else: # 第一次下沉遍历，将叶子节点right指针指向下一个会遍历到的数
                    curr.right = root
                    root = root.left
            else:
                nums.append(root.val)
                root = root.right

        return nums

    def preorder(self, root: None):
        nums = []
        curr = None

        while root:
            if root.left:
                curr = root.left
                while curr.right and curr.right != root:
                    curr = curr.right
                if curr.right == root:
                    curr.right = None
                    root = root.right
                else:
                    nums.append(root.val)
                    curr.right = root
                    root = root.left
            else:
                nums.append(root.val)
                root = root.right

        return nums

    def postorder(self, root: None):
        nums = []
        curr = None

        while root:
            if root.right:
                curr = root.right
                while curr.left and curr.left != root:
                    curr = curr.left
                if curr.left == root:
                    curr.left = None
                    root = root.left
                else:
                    nums.append(root.val)
                    curr.left = root
                    root = root.right
            else:
                nums.append(root.val)
                root = root.left

        nums.reverse()
        return nums


if __name__ == "__main__":
    solution = Solution()

    root = Node(1, None, None)
    node1 = Node(2, None, None)
    node2 = Node(3, None, None)
    node3 = Node(4, None, None)
    node4 = Node(5, None, None)

    root.left = node1
    root.right = node2
    node2.left = node3
    node2.right = node4

    print(solution.inorder(root))
    print(solution.preorder(root))
    print(solution.postorder(root))