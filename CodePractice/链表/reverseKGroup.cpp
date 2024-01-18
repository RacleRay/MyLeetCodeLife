#include "listhead.h"


// https://leetcode.cn/problems/reverse-nodes-in-k-group/submissions/24129840/
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        Node_p dummy = new Node(-1), kpre = dummy;
        dummy->next = head;
        Node_p pre = nullptr;

        while (true) {
            Node_p waiting = head;
            int cnt = k;
            while (cnt && waiting) {
                waiting = waiting->next;
                --cnt;
            }

            // valid nodes group
            if (cnt) break;

            // reverse k node
            Node_p cur = head;
            while (cur != waiting) {
                Node_p wait_in_group = cur->next;
                cur->next = pre;
                pre = cur;
                cur = wait_in_group;
            }

            // connect to main list.
            kpre->next = pre;
            head->next = waiting;
            kpre = head;
            head = waiting;
        }

        return dummy->next;
    }
};