#include "../header.h"


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
    bool hasPathSum(TreeNode* root, int targetSum) {
        if (!root) [[unlikely]] {
            return false;
        }

        if (!root->left && !root->right) {
            return targetSum == root->val;
        }

        return hasPathSum(root->left, targetSum - root->val) 
                || hasPathSum(root->right, targetSum - root->val);
    }

    bool hasPathSum2(TreeNode* root, int targetSum) {
        if (nullptr == root) {
            return false;
        }

        vector<int> res{root->val};
        return dfs(root, targetSum, res);
    }

    // !!! Error not fixed
    bool dfs(TreeNode* root, int targetSum, vector<int> path) {
        if (nullptr == root) {
            return false;
        }

        if ((std::accumulate(path.begin(), path.end(), 0) == targetSum) && !root->left && !root->right) {
            return true;
        } 

        bool left_flag = false, right_flag = false;
        if (root->left) {
            path.push_back(root->left->val);
            left_flag = dfs(root->left, targetSum, path);
        }
        if (root->right) {
            path.push_back(root->right->val);
            right_flag = dfs(root->right, targetSum, path);
        }

        return left_flag || right_flag;
    }


    bool hasPathSum3(TreeNode* root, int targetSum) {
        if (nullptr == root) {
            return false;
        }

        queue<pair<TreeNode*, int>> que;
        que.push(make_pair(root, root->val));
        while (!que.empty()) {
            auto tmp = que.front();
            que.pop();

            if (tmp.second == targetSum && !tmp.first->left && !tmp.first->right) {
                return true;
            }
            if (tmp.first->left) {
                que.push(make_pair(tmp.first->left, tmp.first->left->val + tmp.second));
            }
            if (tmp.first->right) {
                que.push(make_pair(tmp.first->right, tmp.first->right->val + tmp.second));
            }
        }

        return false;
    }


    bool hasPathSum4(TreeNode* root, int targetSum) {
        if (nullptr == root) {
            return false;
        }

        stack<pair<TreeNode*, int>> stk;
        stk.emplace(root, root->val);

        while (!stk.empty()) {
            auto tmp = stk.top();
            stk.pop();

            if (!tmp.first->left && !tmp.first->right && tmp.second == targetSum) {
                return true;
            }
            if (tmp.first->left) {
                stk.emplace(tmp.first->left, tmp.first->left->val + tmp.second);
            } 
            if (tmp.first->right) {
                stk.emplace(tmp.first->right, tmp.first->right->val + tmp.second);
            }
        }

        return false;
    }
};


int main() {
    Solution s;

    return 0;
}