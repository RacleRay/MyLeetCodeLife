from collections import deque


def levelOrder(root):
    if not root:
        return []

    result = []
    queue = deque([root])

    while queue:
        result.append([node.val for node in queue])  # 或者在append时、pop时进行扩充

        qsize = len(queue)
        for _ in range(qsize):
            node = queue.popleft()
            if node.left:
                queue.append(node.left)
            if node.right:
                queue.append(node.right)

    return result


def levelOrderDoubleQueue(root):
    if not root:
        return []

    queue = deque([root])
    res = []

    while queue:
        next_queue = deque([])
        res.append([node.val for node in queue])
        for node in queue:
            if node.left:
                next_queue.append(node.left)
            if node.right:
                next_queue.append(node.right)
        queue = next_queue

    return res


def levelOrderDummyNode(root):
    # None 标记一层结尾
    if not root:
        return []

    queue = deque([root, None])
    res, level = [], []
    while queue:
        node = queue.popleft()

        if node is None:
            res.append(level)
            level = []
            if queue:
                queue.append(None)
            continue

        level.append(node.val)
        if node.left:
            queue.append(node.left)
        if node.right:
            queue.append(node.right)

    return res
