#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

/**
 * Definition for singly-linked list.
 */

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


class Solution
{
public:
    vector<int> reversePrint(ListNode *head)
    {
        if (head == nullptr)
            return vector<int>();

        vector<int> res;
        while (head != nullptr)
        {
            res.push_back(head->val);
            head = head->next;
        }
        // reverse(res.begin(), res.end());
        // return res;
        return vector<int>(res.rbegin(), res.rend());
    }
};
