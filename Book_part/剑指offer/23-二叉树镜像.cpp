#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <stack>
#include <unordered_map>
#include <cmath>
#include <bitset>
#include <stdio.h>
#include <string.h>

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
    TreeNode *mirrorTree(TreeNode *root)
    {
        if (root == nullptr)
            return nullptr;

        swap(root->left, root->right);
        mirrorTree(root->left);
        mirrorTree(root->right);

        return root;
    }

    TreeNode *mirrorTree(TreeNode *root)
    {
        if (root == nullptr)
            return nullptr;

        queue<TreeNode *> q;
        q.push(root);

        while (!q.empty())
        {
            TreeNode *node = q.front();
            q.pop();
            if (node)
            {
                q.push(node->left);
                q.push(node->right);
                swap(node->left, node->right);
            }
        }

        return root;
    }
};