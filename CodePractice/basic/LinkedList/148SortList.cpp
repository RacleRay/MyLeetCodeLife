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
    ListNode* sortList(ListNode* head) {
        return sortList(head, nullptr);
    }

    ListNode* sortList(ListNode* head, ListNode*tail) {
        if (head == nullptr) return head;

        if (head->next == tail) {
            head->next = nullptr;
            return head;
        }

        ListNode* slow = head, *fast = head;
        while (fast != tail) {
            slow = slow->next;
            fast = fast->next;
            if (fast != tail) {
                fast = fast->next;
            }
        }

        ListNode* mid = slow;
        ListNode* leftside = sortList(head, mid);
        ListNode* rightside = sortList(mid, tail);

        return merge(leftside, rightside);
    }

    ListNode* merge(ListNode* head1, ListNode* head2) {
        ListNode* dummy = new ListNode(-1);
        ListNode* travel = dummy, *ptr1 = head1, *ptr2 = head2;

        while (ptr1 != nullptr && ptr2 != nullptr) {
            if (ptr1->val <= ptr2->val) {
                travel->next = ptr1;
                ptr1 = ptr1->next;
            } else {
                travel->next = ptr2;
                ptr2 = ptr2->next;
            }
            travel = travel->next;
        }

        if (ptr1) travel->next = ptr1;
        if (ptr2) travel->next = ptr2;

        return dummy->next;
    }
};