#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@File    :   非递归后续遍历.py
@Author  :   Racle
@Version :   1.0
@Desc    :   None
'''

from dataclasses import dataclass


"""
与前序、中序的非递归方式相同，二叉树的非递归后序遍历也需要借助栈来完成，遍历顺序为左、右、根。

大致思路如下：
1、如果根节点非空，将根节点加入到栈中。
2、如果栈不空，取栈顶元素（暂时不弹出），
    a.如果（左子树已访问过或者左子树为空），且（右子树已访问过或右子树为空），
      则弹出栈顶节点，将其值加入数组，
    b.如果左子树不为空，且未访问过，则将左子节点加入栈中，并标左子树已访问过。
    c.如果右子树不为空，且未访问过，则将右子节点加入栈中，并标右子树已访问过。
3、重复第二步，直到栈空。
"""


@dataclass
class Node:
    val: int = 0
    left: object = None
    right: object = None


class Solution:
    def post_order(self, root):
        result = []
        if not root:
            return result

        stack = []
        stack.append(root)

        prev, curr = None, root
        while len(stack) > 0:
            curr = stack[-1]
            # 当存在左右子树，且当前是向下遍历
            if not prev or prev.left == curr or prev.right == curr:
                if curr.left:
                    stack.append(curr.left)
                elif curr.right:
                    stack.append(curr.right)
            # 从左子树向上回溯时检查右子树
            elif curr.left == prev:
                if curr.right:
                    stack.append(curr.right)
            # 从叶子结点回溯，注意stack中不会将None压栈
            # 1. 左子树为叶子结点，记录并出栈回溯
            # 2. 右子树回溯时，直接记录并出栈回溯
            # 3. 父节点会在右子树出站后，由于从右子树回溯，进入当前分支
            else:
                result.append(curr.val)
                stack.pop()

            # 向下遍历时，prev为curr的父节点
            # 向上回溯时，prev为curr的子节点
            # 转折发生在，左右子树为None，记录val后，pop节点，
            #     下一轮栈顶节点一定是当前节点父节点（左右孩子都适用）
            prev = curr

        return result


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

    print(solution.post_order(root))
