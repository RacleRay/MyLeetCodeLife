#pragma once

#include <iostream>

typedef struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x): val(x), next(nullptr) {}
} Node, *Node_p;