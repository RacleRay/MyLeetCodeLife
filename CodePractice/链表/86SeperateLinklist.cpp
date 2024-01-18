



/**
Definition for singly-linked list.
*/

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        if (nullptr == head) {
            return nullptr;
        }

        ListNode* less = new ListNode(-1);
        ListNode* more = new ListNode(-1);
        ListNode* dummy_less = less;
        ListNode* dummy_more = more;
        ListNode* cur = head;

        while (cur != nullptr) {
            if (cur->val < x) {
                less->next = cur;
                cur = cur->next;
                less = less->next;
                less->next = nullptr;
            } else {
                more->next = cur;
                cur = cur->next;
                more = more->next;
                more->next = nullptr;
            }
        }

        less->next = dummy_more->next;

        ListNode* res = dummy_less->next;

        delete dummy_less;
        delete dummy_more;

        return res;
    }
};