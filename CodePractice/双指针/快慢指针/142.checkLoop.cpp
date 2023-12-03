#include <vector>
#include <iostream>

using namespace std;

/**
 * Definition for singly-linked list.
 * */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if (head == nullptr || head->next == nullptr) return nullptr;
        ListNode* fast = head;
        ListNode* slow = head;

        int flag = 1;
        while (flag) {
            if (!fast || !fast->next) return nullptr;
            fast = fast->next->next;
            slow = slow->next;
            if (fast == slow) flag = 0;
        }

        fast = head;
        while (fast != slow) {
            fast = fast->next;
            slow = slow->next;
        }

        return fast;
    }
};