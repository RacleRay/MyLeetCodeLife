#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <stack>
#include <unordered_map>
#include <cmath>
#include <bitset>
#include <stdio.h>
#include <string.h>

using namespace std;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution
{
public:
    ListNode *getKthFromEnd(ListNode *head, int k)
    {
        // naive
        int count = 0;
        ListNode *node = head;
        while (head != nullptr)
        {
            node = node->next;
            count++;
        }
        count -= (k - 1);
        if (count < 0)
            return nullptr;
        while (count > 0)
        {
            head = head->next;
            count--;
        }
        return head;
    }

    ListNode *getKthFromEnd(ListNode *head, int k){
        ListNode *slow=head;
        ListNode *fast=head;
        while (k--){
            fast = fast->next;
        }
        while (fast!=nullptr){
            slow = slow->next;
            fast = fast->next;
        }
        return slow;
    }
};