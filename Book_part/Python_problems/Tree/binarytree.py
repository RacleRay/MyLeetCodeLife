# python3

class BinaryTreeNode:
    """二叉树性质1：非空二叉树第i层上最多有2^(i-1)个节点。
       二叉树性质2：一颗深度为k的二叉树，最多有2^k - 1个节点，最少有k个节点；
       二叉树性质3：一颗非空二叉树，度为0的节点总是比度为2的节点多1个。
       二叉树性质4：所有节点的度数之和 + 1，等于节点总数。
       二叉树性质5：具有n个节点的完全二叉树，深度为log2(n) + 1.
       二叉树性质6：具有n个节点的完全二叉树，序号为i（从1开始编号）的节点有：
                    1. i>1时，父节点序号为i/2；
                    2. 2i<=n时，有左孩子，序号为2i；
                    3. 2i+1<=n时，有左孩子，序号为2i+1。
    """
    def __init__(self, data=None, leftChild=None, rightChild=None):
        self.data = data
        self.leftChild = leftChild
        self.rightChild = rightChild