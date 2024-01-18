#include "../header.h"


struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (head == nullptr || k == 0 || head->next == nullptr) [[unlikely]] {
            return head;
        }

        int n_node = 1;
        ListNode* p = head;
        while (p->next != nullptr) {
            p = p->next;
            n_node++;
        }

        int at_last = n_node - k % n_node;
        if (at_last == n_node) {
            return head;
        }

        // build loop
        p->next = head;
        while (at_last--) {  // at_last 次
            p = p->next;
        }

        ListNode* res = p->next;
        p->next = nullptr;

        return res;
    }
};