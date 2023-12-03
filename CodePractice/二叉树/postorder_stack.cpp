#include <vector>
#include <stack>

using namespace std;

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// https://leetcode.cn/problems/binary-tree-preorder-traversal/solutions/87526/leetcodesuan-fa-xiu-lian-dong-hua-yan-shi-xbian-2/

class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        if (!root) return res;

        stack<TreeNode *> st1;
        stack<int> st2;
        st1.push(root);
        TreeNode *cur = nullptr;
        
        while (!st1.empty()) {
            cur = st1.top();
            st1.pop();
            st2.push(cur->val);
            if (cur->left) {
                st1.push(cur->left);
            }
            if (cur->right) {
                st1.push(cur->right);
            }
        }

        while (!st2.empty()) {
            res.push_back(st2.top());
            st2.pop();
        }

        return res;
    }



};