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
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
    {
        if (l1 == nullptr)
            return l2;
        if (l2 == nullptr)
            return l1;

        ListNode *res = new ListNode(-1);
        ListNode *ptr = res;

        while (l1 != nullptr && l2 != nullptr)
        {
            if (l1->val <= l2->val)
            {
                ptr->next = l1;
                l1 = l1->next;
            }
            else
            {
                ptr->next = l2;
                l2 = l2->next;
            }
            ptr = ptr->next;
        }

        ptr->next = (l1 ? l1 : l2);
        return res->next;
    }

    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
    {
        if (l1 == nullptr)
            return l2;
        if (l2 == nullptr)
            return l1;

        ListNode *res = new ListNode(-1);
        ListNode *ptr = res;

        merge(l1, l2, ptr);

        return res->next;
    }

    void merge(ListNode *l1, ListNode *l2, ListNode *ptr)
    {
        if (!l1 || !l2)
        {
            ptr->next = (l1 ? l1 : l2);
            return;
        }

        if (l1->val < l2->val)
        {
            ptr->next = l1;
            l1 = l1->next;
        }
        else
        {
            ptr->next = l2;
            l2 = l2->next;
        }

        ptr = ptr->next;
        merge(l1, l2, ptr);
    }
};