#include "listhead.h"

class Solution {
public:
    Node_p addTwoNumber(Node_p l1, Node_p l2) {
        Node_p pt = new Node(-1);
        Node_p dummy = pt;
        Node_p tl1 = l1, tl2 = l2;

        int carry = 0;
        while (tl1 || tl2) {
            if (!tl1) {
                pt->next = new Node((carry + tl2->val) % 10);
                carry = (carry + tl2->val) / 10;
                tl2 = tl2->next;
            } else if (!tl2) {
                pt->next = new Node((carry + tl1->val) % 10);
                carry = (carry + tl1->val) / 10;
                tl1 = tl1->next;
            } else {
                pt->next = new Node((carry + tl1->val + tl2->val) % 10);
                carry = (carry + tl1->val + tl2->val) / 10;
                tl1 = tl1->next;
                tl2 = tl2->next;
            }
            pt = pt->next;
        }

        if (carry) pt->next = new Node(carry);

        return dummy;
    }
};