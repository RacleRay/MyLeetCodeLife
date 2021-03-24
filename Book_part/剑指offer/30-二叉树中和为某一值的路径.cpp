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


//  Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


class Solution
{
public:
    vector<vector<int>> pathSum(TreeNode *root, int target)
    {
        vector<vector<int>> res;

        if (root == nullptr)
            return res;

        vector<int> curpath;

        recursive(root, res, curpath, target);

        // sort(res.begin(), res.end(), [](const vector<int> &a, const vector<int> &b) { return a.size() > b.size(); });

        return res;
    }

    void recursive(TreeNode *root, vector<vector<int>> &res, vector<int> &curpath, int target)
    {
        if (root == nullptr)
            return;

        curpath.push_back(root->val);
        if (root->left == nullptr && root->right == nullptr && target == root->val)
            res.push_back(curpath);
        else
        {
            if (root->left)
                recursive(root->left, res, curpath, target - root->val);
            if (root->right)
                recursive(root->right, res, curpath, target - root->val);
        }
        curpath.pop_back();
    }
};


struct compare{
    bool operator()(const vector<int>& left, const vector<int>& right){
        return left.size() > right.size();
    }
};