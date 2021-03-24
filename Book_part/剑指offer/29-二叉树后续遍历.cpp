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

using namespace std;


// 非递归

class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;

        if (root==nullptr) return res;

        stack<TreeNode*> record;
        record.push(root);
        while (!record.empty()) {
            TreeNode *node = record.top();
            record.pop();

            res.insert(res.begin(), node->val);

            if (node->left != nullptr) record.push(node->left);
            if (node->right != nullptr) record.push(node->right);
        }

        return res;
    }
};