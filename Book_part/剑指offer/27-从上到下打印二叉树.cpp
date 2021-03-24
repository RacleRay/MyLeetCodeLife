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
#include <limits.h>
#include <queue>

using namespace std;


class Solution {
public:
    vector<int> levelOrder(TreeNode* root) {
        if (root == nullptr) return vector<int>();

        queue<TreeNode*> q;
        q.push(root);

        TreeNode *node = nullptr;
        vector<int> res;
        while (!q.empty()) {
            node = q.front();
            q.pop();
            res.push_back(node->val);
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }

        return res;
    }
};