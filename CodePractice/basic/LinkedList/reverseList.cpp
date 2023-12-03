#include "listhead.h"


class Solution {
public:
    Node_p reverseListRecurssion(Node_p head) {
        if (!head || !head->next) return head;

        Node_p new_head = reverseListRecurssion(head);
        head->next->next = head;
        head->next = nullptr;

        return new_head;
    }

    Node_p reverseListRecurssion2(Node_p head, Node_p pre=nullptr) {
        if (!head) return pre;
        Node_p next = head->next;
        head->next = pre;
        return reverseListRecurssion2(next, head);
    }

    Node_p reverseList(Node_p head) {
        if (!head || !head->next) return head;

        Node_p pre = nullptr, cur = head, waiting = nullptr;
        while (cur) {
            waiting = cur->next;
            cur->next = pre;
            pre = cur;
            cur = waiting;
        }

        return pre;
    }
};