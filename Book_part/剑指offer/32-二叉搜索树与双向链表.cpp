#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <stack>
#include <unordered_map>
#include <functional>
#include <cmath>
#include <bitset>
#include <stdio.h>
#include <string.h>
#include <limits.h>

using namespace std;

// Definition for a Node.
class Node
{
public:
    int val;
    Node *left;
    Node *right;

    Node() {}

    Node(int _val)
    {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node(int _val, Node *_left, Node *_right)
    {
        val = _val;
        left = _left;
        right = _right;
    }
};

class Solution
{
public:
    Node *treeToDoublyList(Node *root)
    {
        Node *head = nullptr;
        Node *pre = nullptr;
        stack<Node *> stk;

        while (!stk.empty() || root)
        {
            while (root != nullptr)
            {
                stk.push(root);
                root = root->left;
            }
            if (!stk.empty())
            {
                root = stk.top();
                stk.pop();
                if (pre != nullptr)
                {
                    pre->right = root;
                    root->left = pre;
                }
                else
                {
                    head = root;
                }

                pre = root;
                root = root->right;
            }
        }

        return head;
    }


    Node *treeToDoublyList(Node *root)
    {
        if (root == nullptr)
            return nullptr;

        vector<Node *> result;
        stack<Node *> stk;

        while (!stk.empty() || root != nullptr)
        {
            if (root != nullptr)
            {
                stk.push(root);
                root = root->left;
            }
            else
            {
                root = stk.top();
                stk.pop();
                result.push_back(root);
                root = root->right;
            }
        }

        for (int i = 0; i < result.size() - 1; i++)
        {
            result[i]->right = result[i + 1];
            result[i + 1]->left = result[i];
        }

        result[0]->left = result[result.size() - 1];
        result[result.size() - 1]->right = result[0];

        return result[0];
    }
};


// int main(int argc, char **argv){
//     Node a = Node(4);
//     Node b = Node(2);
//     Node c = Node(5);
//     Node d = Node(1);
//     Node e = Node(3);

//     a.left = &b;
//     a.right = &c;
//     b.left = &d;
//     b.right = &e;

//     Solution s = Solution();
//     Node* res = s.treeToDoublyList(&a);
// }