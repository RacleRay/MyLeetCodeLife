# python3

from helper import LNode, print_list, construct_list


def reverse(first):
    """没有头节点，链表整个翻转"""
    if first == None or first.next == None:
        return first

    prev = first
    cur = first.next
    # 作为尾节点
    prev.next = None
    while cur != None:
        next = cur.next

        cur.next = prev
        prev = cur

        cur = next

    # 返回尾节点
    return prev


def reverse_k(head, k):
    if head == None or head.next == None:
        return None

    # init
    prev = head
    begin = head.next
    end = None
    next_pre = None

    i = 1
    while begin != None:

        end = begin
        while i < k:

            if end.next != None:
                end = end.next
            else:
                return

            i += 1

        # splite and reverse
        next_pre = end.next
        end.next = None
        prev.next = reverse(begin)

        # combine two part
        begin.next = next_pre

        # next loop
        prev = begin
        begin = next_pre

        i = 1


if __name__ == "__main__":
    head = construct_list()
    print_list(head)
    print()

    reverse_k(head, 3)

    print('After: ')
    print_list(head)
