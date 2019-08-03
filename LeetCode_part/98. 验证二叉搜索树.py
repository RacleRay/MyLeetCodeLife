"""
给定一个二叉树，判断其是否是一个有效的二叉搜索树。

假设一个二叉搜索树具有如下特征：

节点的左子树只包含小于当前节点的数。
节点的右子树只包含大于当前节点的数。
所有左子树和右子树自身必须也是二叉搜索树。
示例 1:

输入:
    2
   / \
  1   3
输出: true
示例 2:

输入:
    5
   / \
  1   4
     / \
    3   6
输出: false
解释: 输入为: [5,1,4,null,null,3,6]。
     根节点的值为 5 ，但是其右子节点值为 4 。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/validate-binary-search-tree
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
"""
# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution(object):
    def isValidBST(self, root):
        """
        :type root: TreeNode
        :rtype: bool
        """
        # def helper(node, lower = float('-inf'), upper = float('inf')):
        #     if not node:
        #         return True

        #     val = node.val
        #     if val <= lower or val >= upper:  # 检查是否左边小，右边大
        #         return False

        #     if not helper(node.right, val, upper):  # upper，lower相当于拿来站位，只关心一边
        #         return False
        #     if not helper(node.left, lower, val):
        #         return False
        #     return True

        # return helper(root)

        # 中序遍历，为升序
        self.prev = None
        return self.helper(root)

        def helper(self, root):
            if root is None:  # 空为有效的bst
                return True
            if not self.helper(root.left):  # 递归到最左，返回true，若出现false，递归返回false
                return False
            if self.prev and self.prev.val >= root.val:  # 每个点的前一个必须比当前小
                return False
            self.prev = root  # 保存前一个root
            return self.helper(root.right)
        return helper(root)