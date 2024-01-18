/**
Definition for a binary tree node.
*/
#include <cstddef>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;


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
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        TreeNode *root = nullptr;
        root = helper(preorder, inorder, 0, preorder.size() - 1, 0, inorder.size() - 1);
        return root;
    }

    TreeNode *helper(vector<int>& preorder, vector<int>& inorder, int pre_start, int pre_end, int in_start, int in_end) {
        if (in_start > in_end || pre_start > pre_end) { 
            return nullptr;
        }

        TreeNode* root = new TreeNode(preorder[pre_start]);
        if (pre_start == pre_end) {
            return root;
        }

        int idx = in_start;
        while (preorder[pre_start] != inorder[idx]) {
            idx++;
        }

        int left_part_start = pre_start + 1;
        int left_part_end = pre_start + 1 + ((idx - 1) - in_start);

        int right_part_start = left_part_end + 1;
        int right_part_end = pre_end;

        root->left = helper(preorder, inorder, 
                            left_part_start, left_part_end, 
                            in_start, idx - 1);
        root->right = helper(preorder, inorder, 
                            right_part_start, right_part_end, 
                            idx + 1, in_end);
        
        return root;
    }

    TreeNode* helper_in_post(vector<int>& in, vector<int>& post, int in_start, int in_end,
        int post_start, int post_end) {
        if (in_start > in_end || post_start > post_end) return nullptr;

        TreeNode* root = new TreeNode(post[post_end]);
        if (post_start == post_end) return root;

        int idx = in_start;
        while (post[post_end] != in[idx]) {
            ++idx;
        }

        root->left = helper_in_post(in, post, in_start, idx - 1,
                                    post_start, post_start + (idx - 1 - in_start));
        root->right = helper_in_post(in, post, idx + 1, in_end, 
                                    post_end - 1 - (in_end - (idx + 1)), post_end - 1);
    
        return root;
    }

    TreeNode* helper_pre_post(vector<int>& pre, vector<int>& post, int pre_start, int pre_end,
        int post_start, int post_end) {
        if (pre_start > pre_end || post_start > post_end) return nullptr;

        TreeNode* root = new TreeNode(pre[pre_start]);
        if (pre_start == pre_end) return root;

        int idx = post_start;
        // 根节点的左孩子，找到在post order中的位置
        while (pre[pre_start + 1] != post[idx]) {
            ++idx;
        }

        root->left = helper_pre_post(pre, post,
                                    pre_start + 1, pre_start + 1 + idx - post_start,
                                    post_start, idx);
        root->right = helper_pre_post(pre, post, 
                                    pre_start + 1 + idx - post_start, pre_end, 
                                    idx + 1, post_end - 1);

        return root;
    }
};