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
    ListNode *reverseList(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode dummy = ListNode(0);

        ListNode *pre = &(ListNode(0));
        ListNode *cur = nullptr;
        ListNode *tmp = nullptr;

        pre->next = head;
        cur = head->next;
        head->next = nullptr;

        while (cur != nullptr)
        {
            tmp = cur;
            cur = cur->next;
            tmp->next = pre->next;
            pre->next = tmp;
        }

        return pre->next;
    }

    ListNode *reverseList(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *pre = nullptr;
        ListNode *cur = head;
        ListNode *next = cur->next;

        while (next != nullptr){
            cur->next = pre;
            pre = cur;
            cur = next;
            next = next->next;
        }

        cur->next = pre;

        return cur;
    }
};