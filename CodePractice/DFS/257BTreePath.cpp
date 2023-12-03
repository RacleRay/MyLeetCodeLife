#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>


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
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> res;
        if (root == nullptr)
            return res;

        dfs(res, "", root);

        return res;
    }

    void dfs(vector<string>& res, string path, TreeNode *root) {
        if (root == nullptr) return;

        if (root->left == nullptr && root->right == nullptr) {
            path += to_string(root->val);
            res.push_back(path);
            return;
        }

        path += to_string(root->val) + "->";
        dfs(res, path, root->left);
        dfs(res, path, root->right);
    }


    vector<string> binaryTreePaths_DFS_noRec(TreeNode* root) {
        vector<string> res;
        if (!root) return res;

        stack<TreeNode*> nodeS;
        stack<string> strS;

        nodeS.push(root);
        strS.push(to_string(root->val));

        while (!nodeS.empty()) {
            string path = strS.top();
            strS.pop();
            TreeNode* node = nodeS.top();
            nodeS.pop();

            if (node->left == nullptr && node->right == nullptr) {
                res.push_back(path);
            }
            if (node->right) {
                nodeS.push(node->right);
                strS.push(path + "->" + to_string(node->right->val));
            }
            if (node->left){
                nodeS.push(node->left);
                strS.push(path + "->" + to_string(node->left->val));
            }
        }

        return res;
    }


    vector<string> binaryTreePaths_BFS(TreeNode* root) {
        vector<string> res;
        if (!root) return res;

        queue<TreeNode *> nodeQ;
        queue<string> strQ;
        nodeQ.push(root);
        strQ.push(to_string(root->val));

        while (!nodeQ.empty()) {
            TreeNode* node = nodeQ.front();
            string path = strQ.front();
            nodeQ.pop();
            strQ.pop();

            if (node->left == nullptr && node->right == nullptr) {
                res.push_back(path);
            }
            if (node->right) {
                nodeQ.push(node->right);
                strQ.push(path + "->" + to_string(node->right->val));
            }
            if (node->left) {
                nodeQ.push(node->left);
                strQ.push(path + "->" + to_string(node->left->val));
            }
        }

        return res;
    }
};