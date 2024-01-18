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
    ListNode* deleteDuplicates(ListNode* head) {
        if (!head || !head->next) return head;

        ListNode* dummy = new ListNode(-1, head);
        ListNode* pre = dummy, *cur = head, *travel = head;

        while (cur) {
            travel = cur->next;
            if (cur->val == travel->val) {
                ListNode *tmp = cur;
                pre->next = cur->next;
                delete tmp;
                cur = pre->next;
            } else {
                pre = cur;
                cur = cur->next;
            }
        }

        return dummy->next;
    }
};