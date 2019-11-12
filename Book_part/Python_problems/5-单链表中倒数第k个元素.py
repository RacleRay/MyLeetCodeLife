# python3

from helper import LNode, construct_list, print_list


def find_last_k(head, k):
    """快慢指针，快k步。T:O(N), Space: O(1)"""
    if head == None or head.next == None:
        return head

    slow_p = head.next
    fast_p = head.next

    # k step
    i = 0
    while i < k and fast_p != None:
        fast_p = fast_p.next
        i += 1

    # k取值过大
    if i < k:
        return None

    # 同进
    while fast_p != None:
        slow_p = slow_p.next
        fast_p = fast_p.next

    return slow_p


if __name__ == '__main__':
    head = construct_list()
    print('List：')
    print_list(head)

    result = find_last_k(head, 3)
    if result is not None:
        print('Result: ', result.data)
