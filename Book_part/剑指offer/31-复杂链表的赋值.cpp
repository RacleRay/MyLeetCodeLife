#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <stack>
#include <unordered_map>
#include <functional>
#include <cmath>
#include <bitset>
#include <stdio.h>
#include <string.h>
#include <limits.h>

using namespace std;


// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};


class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (head==nullptr) return nullptr;

        unordered_map<Node*, Node*> umap;

        for (Node* p = head; p != nullptr; p = p->next) {
            umap[p] = new Node(p->val);
        }

        for (Node* p = head; p != nullptr; p = p->next) {
            umap[p]->next = umap[p->next];
            umap[p]->random = umap[p->random];
        }

        return umap[head];
    }


    Node* copyRandomList(Node* head){
        unordered_map<Node*, Node*> umap;

        std::function<Node*(Node*)> func;

        func = [&umap, &func](Node* phead) -> Node*{
            if (phead==nullptr) return nullptr;
            Node* node = new Node(phead->val);
            umap[phead] = node;
            node->next = func(phead->next);

            if (phead->random!=nullptr)
                node->random = umap[phead->random];

            return node;
        };

        return func(head);
    }
};
