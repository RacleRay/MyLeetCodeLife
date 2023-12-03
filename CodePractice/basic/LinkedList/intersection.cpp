#include "listhead.h"


// https://leetcode-cn.com/problems/intersection-of-two-linked-lists/
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        Node_p ta = headA, tb = headB;

        while (ta != tb) {
            // 相交节点前，让 ta tb 一定走过相同长度的路径
            ta = ta == nullptr ? tb: ta->next;
            tb = tb == nullptr ? ta: tb->next;
        }

        return ta;
    }
};
