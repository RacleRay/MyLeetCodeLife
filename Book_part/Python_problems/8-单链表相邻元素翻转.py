# python3

from helper import LNode, print_list, construct_list


def reverse(head):
    if head == None or head.next == None:
        return None

    cur = head.next
    prev = head  # 前驱
    next = None

    while cur != None and cur.next != None:
        next = cur.next.next  # 后继的后继
        prev.next = cur.next  # 沿着轨迹
        cur.next.next = cur
        cur.next = next

        prev = cur  # 下一步
        cur = cur.next


if __name__ == "__main__":
    head = construct_list()
    print_list(head)
    print()

    reverse(head)

    print('After: ')
    print_list(head)

