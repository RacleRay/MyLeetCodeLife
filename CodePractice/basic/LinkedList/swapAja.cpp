#include "listhead.h"


class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if (!head || !head->next) return head;

        Node_p dummy = new Node(-1);
        dummy->next = head;
        Node_p pre = dummy, cur = head;
        while (cur && cur->next) {
            Node_p waiting = cur->next->next;
            cur->next->next = cur;
            pre->next = cur->next;
            cur->next = waiting;

            pre = cur;
            cur = waiting;
        }

        return dummy->next;
    }
};