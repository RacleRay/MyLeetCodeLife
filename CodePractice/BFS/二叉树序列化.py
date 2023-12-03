#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@File    :   二叉树序列化.py
@Author  :   Racle
@Version :   1.0
@Desc    :   None
'''

"""

"""

from dataclasses import dataclass


@dataclass
class Node:
    val: int = 0
    left: object = None
    right: object = None


class Solution:
    def serialize(self, root):
        if root is None:
            return "{}"

        queue = [root]
        index = 0
        while index < len(queue):
            if queue[index] is not None:
                queue.append(queue[index].left)
                queue.append(queue[index].right)
            index += 1

        while queue[-1] is None:
            queue.pop()

        return '{%s}' % ','.join([str(node.val) if node is not None else '#'
                                  for node in queue])

    def deserialize(self, data):
        data = data.strip('\n')

        if data == '{}':
            return None

        vals = data[1: -1].split(',')

        root = Node(int(vals[0]))
        queue = [root]
        is_left = True
        index = 0

        for val in vals:
            if val != '#':
                node = Node(int(val))
                if is_left:
                    queue[index].left = node
                else:
                    queue[index].right = node
                queue.append(node)

            if not is_left:
                index += 1
            is_left = not is_left

        return root


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

    ss = solution.serialize(root)
    print(ss)
    sroot = solution.deserialize(ss)
    print(root.val, root.left.val, root.right.val,
          root.right.left.val, root.right.right.val)
