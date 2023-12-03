#include "../header.h"


/**
 * @brief 这里我们就可以使用水库采 样：遍历一次链表，在遍历到第m个节点时，有 1
        m 的概率选择这个节点覆盖掉之前的节点选择。

        我们提供一个简单的，对于水库算法随机性的证明。对于长度为 n 的链表的第m个节点，
        最后被采样的充要条件是它被选择，且之后的节点都没有被选择。
        这种情况发生的概率为 1/m × m/m+1 × m+1/m+2 × · · · × n−1/n = 1/n。
        
        因此每个点都有均等的概率被选择。
 * 
 */

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
    ListNode* head;
public:
    Solution(ListNode* head): head(head) {
    }
    
    int getRandom() {
        int ans = head->val;
        ListNode* cur = head->next;
        int choose_from = 2;
        while (cur) {
            if (rand() % choose_from == 0) {
                ans = cur->val;
            }
            ++choose_from;
            cur = cur->next;
        }

        return ans;
    }
};