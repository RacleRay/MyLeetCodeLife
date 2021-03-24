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
    bool isSubStructure(TreeNode *A, TreeNode *B)
    {
        if (!A || !B)
            return false;

        return recur(A, B) || isSubStructure(A->left, B) || isSubStructure(A->right, B);
    }

    bool recur(TreeNode *A, TreeNode *B)
    {
        if (!B)
            return true;
        if (!A)
            return false;

        if (A->val == B->val)
            return recur(A->left, B->left) && recur(A->right, B->right);
        else
            return false;
    }
};