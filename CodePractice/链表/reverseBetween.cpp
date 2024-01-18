#include "listhead.h"


class Solution {
    Node_p reverseBetween(Node_p head, int m, int n) {
        if (!head || !head->next) return head;

        int start_i = 1;
        Node_p dummy = new Node(-1);
        Node_p pre = dummy, cur = head;

        while (start_i < m) {
            pre = pre->next;
            ++start_i;
        }
        cur = pre->next;

        Node_p record = pre;

        while (m <= n) {
            Node_p waiting = cur->next;
            cur->next = pre;
            pre = cur;
            cur = waiting;
            ++m;
        }

        // note: 此时cur 和 pre的位置
        record->next->next = cur;
        record->next = pre;

        return dummy->next;
    }
};