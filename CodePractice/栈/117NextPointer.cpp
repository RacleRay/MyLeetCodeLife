#include "../header.h"


class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};


class Solution {
public:
    Node* connect(Node* root) {
        Node* ans = root;
        if (root == nullptr) {
            return ans;
        }
        auto cur = root;
        while (cur) {
            auto head = new Node(-1), tail = head;
            for (auto i = cur; i != nullptr; i = i->next) {
                if (i->left) {
                    tail->next = i->left;
                    tail = tail->next;
                }
                if (i->right) {
                    tail->next = i->right;
                    tail = tail->next;
                }
                cur = head->next;
            }
        }

        return ans;
    }
};