#include <stack>
#include <vector>
#include <iostream>


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


class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        if (root != nullptr) return res;

        stack<TreeNode *> stk;

        while (root) {
            stk.push(root);
            root = root->left;
        }

        int tmp = 0;
        while (!stk.empty()) {
            tmp = getnext(stk);
            res.push_back(tmp);
        }

        return res;
    }

    int getnext(stack<TreeNode *> stk) {
        TreeNode *cur = stk.top();
        if (cur->right != nullptr) {
            TreeNode *travel = cur->right;
            while (travel) {
                stk.push(travel);
                travel = travel->left;
            }
        } else {
            stk.pop();
            TreeNode *travel = cur;
            while (travel && stk.top()->right == travel) {
                travel = stk.top();
                stk.pop();
            }
        }

        return cur->val;
    }

    // ===========================================================
    vector<int> inorderTravel(TreeNode *root) {
        vector<int> res;
        if (root != nullptr) return res;

        stack<TreeNode *> stk;
        TreeNode *cur = root;
        
        while (cur || !stk.empty()) {
            while (cur) {
                stk.push(cur);
                cur = cur->left;
            }

            cur = stk.top();
            res.push_back(cur->val);
            stk.pop();

            cur = cur->right;
        }

        return res;
    }
};