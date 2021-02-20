#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <unordered_map>

using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution
{
public:
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
    {
        if (preorder.size() == 0 || inorder.size() == 0)
        {
            return nullptr;
        }

        TreeNode *root = new TreeNode(preorder[0]);
        int mid = distance(inorder.begin(),
                           find(inorder.begin(), inorder.end(), preorder[0]));
        vector<int> pre_left(preorder.begin() + 1, preorder.begin() + mid + 1);
        vector<int> pre_right(preorder.begin() + mid + 1, preorder.end());
        vector<int> in_left(inorder.begin(), inorder.begin() + mid);
        vector<int> in_right(inorder.begin() + mid + 1, inorder.end());

        root->left = buildTree(pre_left, in_left);
        root->right = buildTree(pre_right, in_right);
        return root;
    }

    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
    {
        unordered_map<int, int> umap;
        for (int i = 0; i < inorder.size(); ++i)
        {
            umap.insert({inorder[i], i});
        }

        return recursive(preorder, umap, 0, 0, inorder.size() - 1);
    }

    //前序的root  中序的start和end
    TreeNode *recursive(vector<int> &preorder, unordered_map<int, int> &umap,
                        int rootIdx, int start, int end)
    {
        if (start > end)
            return nullptr;
        TreeNode *root = new TreeNode(preorder[rootIdx]);
        int inorderIdx = umap[preorder[rootIdx]];

        root->left = recursive(preorder, umap, rootIdx + 1, start, inorderIdx - 1);
        root->right = recursive(preorder, umap, rootIdx + 1 + inorderIdx - start,
                                inorderIdx + 1, end);
        return root;
    }
};