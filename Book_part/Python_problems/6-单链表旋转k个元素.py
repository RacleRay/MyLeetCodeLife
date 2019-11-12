# python3

from helper import LNode, construct_list, print_list


# 1 2 3 4 5 6 7 => 5 6 7 1 2 3 4
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

    # 同进，有一点小变化，slow_p在倒数第k + 1的位置
    while fast_p.next != None:
        slow_p = slow_p.next
        fast_p = fast_p.next

    return slow_p, fast_p


def rotate_k(head, k):
    slow_p, fast_p = find_last_k(head, k)

    if slow_p == None or slow_p == head:
        return None

    tmp = slow_p
    slow_p = slow_p.next

    fast_p.next = head.next
    head.next = slow_p
    tmp.next = None


if __name__ == '__main__':
    head = construct_list()
    print('List：')
    print_list(head)
    print()

    rotate_k(head, 3)

    print('After：')
    print_list(head)