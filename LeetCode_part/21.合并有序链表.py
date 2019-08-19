class Solution(object):
    def mergeTwoLists(self, l1, l2):
        """
        :type l1: ListNode
        :type l2: ListNode
        :rtype: ListNode
        """
        # method1
        # if l1 is not None and l2 is not None:
        #     if l1.val > l2.val:
        #         l1, l2 = l2, l1  # l1指向较小值
        #     l1.next = self.mergeTwoLists(l1.next, l2) # next指向下一个较小值
        # return l1 or l2

        newList = ListNode(None)
        prev = newList
        while l1 is not None and l2 is not None:
            if l1.val <= l2.val:
                prev.next = l1
                l1 = l1.next
            else:
                prev.next = l2
                l2 = l2.next
            prev = prev.next

        prev.next = l1 if l1 is not None else l2  # None或者两者不为None的一个

        return newList.next


