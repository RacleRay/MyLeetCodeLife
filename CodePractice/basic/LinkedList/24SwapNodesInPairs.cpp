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
    ListNode* swapPairs(ListNode* head) {
        if (!head || !head->next) return head;

        ListNode* dummy = new ListNode(-1);
        dummy->next = head;
        ListNode* pre = dummy, *cur = head;
        while (cur && cur->next) {
            ListNode* waiting = cur->next->next;
            cur->next->next = cur;
            pre->next = cur->next;
            cur->next = waiting;

            pre = cur;
            cur = waiting;
        }

        return dummy->next;
    }

    ListNode* swapPairs2(ListNode* head) {
        ListNode *p = head, *s;  // p first, s second

        if (p && p->next) {
            s = p->next;
            p->next = s->next;
            s->next = p;
            head = s;
            while (p->next && p->next->next) {
                s = p->next->next;
                p->next->next = s->next;
                s->next = p->next;
                p->next = s;
                p = s->next;
            }
        }

        return head;
    }
};