from collections import deque

# Definition for a Node.
class Node:
    def __init__(self, val=None, children=None):
        self.val = val
        self.children = children

class Solution:
    def maxDepth(self, root: 'Node') -> int:
        if not root: return 0

        ans = 0
        queue = deque([root])
        while queue:
            level_size = len(queue)
            while level_size:
                cur = queue.popleft()
                level_size -= 1
                for node in cur.children:
                    queue.append(node)
            ans += 1

        return ans